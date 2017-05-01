#include "CinderLibIgl.h"
#include "cinder/app/App.h"
#include <igl/read_triangle_mesh.h>
#include <igl/copyleft/tetgen/tetrahedralize.h>
#include <igl/barycenter.h>
#include <igl/edges.h>

using namespace std;
using namespace ci;
using namespace ci::app;

namespace cinder {
IglMesh::IglMesh() {
  fmt = TriMesh::Format().positions().normals().colors();
  initFromFormat(fmt);
}

IglMesh::IglMesh(const std::string str) {
  Eigen::MatrixXd V;
  Eigen::MatrixXi F;
  if (igl::read_triangle_mesh(str, V, F)) {
    setMesh(V, F);
  } else {
    cout << "error reading mesh!"
         << "\n";
  }
}

IglMesh::~IglMesh() {}

bool IglMesh::loadMesh(const std::string str) {
  Eigen::MatrixXd V;
  Eigen::MatrixXi F;
  if (igl::read_triangle_mesh(str, V, F)) {
    setMesh(V, F);
    return true;
  } else {
    cout << "error reading mesh!"
         << "\n";
    return false;
  }
}

void IglMesh::setMesh(Eigen::MatrixXd V, Eigen::MatrixXi F) {
  this->clear();
  mV=V;
  mF=F;
  igl::edges(mF, mE);
  cout << "edges="<<mE << "\n"; 

  aabbTree.init(mV,mF);
  // Compute per-face normals
  igl::per_face_normals(mV,mF,N_faces);

  // Compute per-vertex normals
  igl::per_vertex_normals(mV,mF,N_vertices);

  // Compute per-corner normals, |dihedral angle| > 20 degrees --> crease
  igl::per_corner_normals(mV,mF,20,N_corners);
  // cout << "N_vertices="<<N_vertices << "\n"; 
  // cout << "N_faces="<<N_faces<< "\n"; 
  // cout << "N_corners="<<N_corners<< "\n"; 
  // data.clear();
  // data.set_mesh(V, F);
  // data.set_normals(N_faces);
  // data.set_normals(N_corners);
  // V_vbo= V.transpose().cast<float>();
  // F_vbo= F.transpose().cast<unsigned>();
  // V_normals_vbo= N_vertices.transpose().cast<float>();
  // V_normals_vbo= N_faces.transpose().cast<float>();
  // V_normals_vbo = N_corners.transpose().cast<float>()
  // V_normals_vbo = (data.F_normals.transpose()).cast<float>();
  this->appendPositions((glm::vec3*)(Eigen::MatrixXf(mV.transpose().cast<float>())).data(), mV.rows());
  this->appendIndices(Eigen::Matrix<unsigned, Eigen::Dynamic, Eigen::Dynamic>(mF.transpose().cast<unsigned>()).data(), mF.size());
  this->appendNormals((glm::vec3*)Eigen::MatrixXf(N_vertices.transpose().cast<float>()).data(), N_vertices.rows());
}

  void IglMesh::tetrahedralize() {
    igl::copyleft::tetgen::tetrahedralize(mV,mF,"pq1.414",mTV,mTT,mTF);
  }
}
