#include "CinderLibIgl.h"
#include "cinder/app/App.h"
#include <igl/read_triangle_mesh.h>
#include <igl/barycenter.h>
#include <igl/edges.h>

using namespace std;
using namespace ci;
using namespace ci::app;

namespace cinder {
    IglMesh::IglMesh() {
      fmt = TriMesh::Format().positions().normals();
      initFromFormat(fmt);
      bufferLayout = {
              gl::VboMesh::Layout().usage(GL_DYNAMIC_DRAW).attrib(geom::Attrib::POSITION, 3),
              gl::VboMesh::Layout().usage(GL_DYNAMIC_DRAW).attrib(geom::Attrib::COLOR, 3)
      };
    }

    IglMesh::IglMesh(const std::string str) {
      fmt = TriMesh::Format().positions().normals();
      initFromFormat(fmt);
      bufferLayout = {
              gl::VboMesh::Layout().usage(GL_DYNAMIC_DRAW).attrib(geom::Attrib::POSITION, 3),
              gl::VboMesh::Layout().usage(GL_DYNAMIC_DRAW).attrib(geom::Attrib::COLOR, 3)
      };
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


    void IglMesh::setColor(Eigen::MatrixXd C) {
      if (C.size() == 0) {
        fmt = TriMesh::Format().positions().normals();
        initFromFormat(fmt);
      } else {
        fmt = TriMesh::Format().positions().normals().colors();
        initFromFormat(fmt);
      }
      Eigen::MatrixXf C_vbo = C.transpose().cast<float>();
      this->mColors = std::vector<float>(C_vbo.data(), C_vbo.data() + C_vbo.size());
    };

    void IglMesh::setMesh(Eigen::MatrixXd V, Eigen::MatrixXi F, Eigen::MatrixXd C) {
      this->clear();
      mV = V;
      mF = F;
      mC = C;
      igl::edges(mF, mE);
      // cout << "edges="<<mE << "\n";

      aabbTree.init(mV, mF);
      // Compute per-face normals
      igl::per_face_normals(mV, mF, N_faces);

      // Compute per-vertex normals
      igl::per_vertex_normals(mV, mF, N_vertices);

      // Compute per-corner normals, |dihedral angle| > 20 degrees --> crease
      igl::per_corner_normals(mV, mF, 20, N_corners);
      // cout << "N_vertices="<<N_vertices << "\n";
      // cout << "N_faces="<<N_faces<< "\n";
      // cout << "N_corners="<<N_corners<< "\n";
      Eigen::MatrixXf V_vbo = V.transpose().cast<float>();
      Eigen::Matrix<unsigned, Eigen::Dynamic, Eigen::Dynamic> F_vbo = F.transpose().cast<unsigned>();
      Eigen::MatrixXf C_vbo;
      if (!C.size())
        C_vbo = Eigen::MatrixXf::Ones(V_vbo.rows(), V_vbo.cols());
      else
        C_vbo = C.transpose().cast<float>();
      // Eigen::MatrixXf C_vbo= Eigen::MatrixXf::Zero(V.cols(),V.rows())+Eigen::MatrixXf::Ones(V.cols(),V.rows());
      // Eigen::MatrixXf C_vbo= Eigen::MatrixXf::Random(V.cols(),V.rows())+Eigen::MatrixXf::Ones(V.cols(),V.rows());
      Eigen::MatrixXf V_normals_vbo = N_vertices.transpose().cast<float>();
      // V_normals_vbo= N_faces.transpose().cast<float>();
      // V_normals_vbo = N_corners.transpose().cast<float>()
      this->mPositions = std::vector<float>(V_vbo.data(), V_vbo.data() + V_vbo.size());
      this->mIndices = std::vector<uint32_t>(F_vbo.data(), F_vbo.data() + F_vbo.size());

      this->mNormals.clear();
      // (glm::vec3*)V_normals_vbo,V_normals_vbo.data()+V_normals_vbo.size()
      // this->mNormals=std::vector<vec3>(V_normals_vbo.data(),V_normals_vbo.data()+V_normals_vbo.size());
      // this->mColors=std::vector<float>(C_vbo.data(),C_vbo.data()+C_vbo.size());
      this->appendNormals((glm::vec3 *) Eigen::MatrixXf(N_vertices.transpose().cast<float>()).data(),
                          N_vertices.rows());
      // this->appendColors((Color*)(Eigen::MatrixXf(mC.transpose().cast<float>())).data(),mC.rows());
      // mVboMeshRef=gl::VboMesh::create(*this,bufferLayout);

      mVboMeshRef = gl::VboMesh::create(V.rows(), GL_TRIANGLES, bufferLayout, F.size(), GL_UNSIGNED_INT);
      mVboMeshRef->bufferAttrib(geom::Attrib::POSITION, V_vbo.size() * sizeof(float), (float *) V_vbo.data());
      mVboMeshRef->bufferAttrib(geom::Attrib::COLOR, C_vbo.size() * sizeof(float), (float *) C_vbo.data());
      mVboMeshRef->bufferIndices(F_vbo.size() * sizeof(uint), (uint *) (F_vbo.data()));
      // std::cout<<"\nVertices=\n"<<V;
      // std::cout<<"\nFaces=\n"<<F;
    }
}
