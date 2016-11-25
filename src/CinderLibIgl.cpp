#include "CinderLibIgl.h"
#include "cinder/app/App.h"
#include <igl/read_triangle_mesh.h>

using namespace std;
using namespace ci;
using namespace ci::app;

namespace cinder {
IglMesh::IglMesh() {
  fmt = TriMesh::Format().positions().normals().colors();
}

IglMesh::IglMesh(const std::string str) {
  igl::read_triangle_mesh(str, V, F);
  setMesh(V, F);
}

IglMesh::~IglMesh() {}

void IglMesh::setMesh(Eigen::MatrixXd V, Eigen::MatrixXi F) {
  data.seti_mesh(V, F);
  V_vbo = (data.V.transpose()).cast<float>();
  F_vbo = (data.F.transpose()).cast<unsigned>();
  V_normals_vbo = (data.V_normals.transpose()).cast<float>();
  this->appendPositions((glm::vec3*)V_vbo.data(), V.rows());
  this->appendIndices(F_vbo.data(), F_vbo.size());
  this->appendNormals((glm::vec3*)V_normals_vbo.data(), V.rows());
}
}
