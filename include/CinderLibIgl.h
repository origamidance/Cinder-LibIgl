/**
 *
 *
 */

#pragma once

#include "cinder/gl/VboMesh.h"
#include "cinder/TriMesh.h"
#include "cinder/Color.h"
#include "cinder/gl/Batch.h"
#include <igl/igl_inline.h>
#include <igl/per_vertex_normals.h>
#include <igl/per_face_normals.h>
#include <igl/per_corner_normals.h>
#include <igl/AABB.h>

namespace cinder {
  typedef std::shared_ptr<class IglMesh> IglMeshRef;

  class IglMesh {
  public:
    IglMesh();

    IglMesh(const std::string str);

    IglMesh(Eigen::MatrixXd V, Eigen::MatrixXi F, Eigen::MatrixXd C = Eigen::MatrixXd()) {
      IglMesh();
      setMesh(V, F, C);
    };

    virtual ~IglMesh();

    bool loadMesh(const std::string str);

    void setMesh(Eigen::MatrixXd V, Eigen::MatrixXi F, Eigen::MatrixXd C = Eigen::MatrixXd());

    void setColor(Eigen::MatrixXd C);

    void setShader(gl::GlslProgRef shader);

    void draw();

  public:
    gl::VboMeshRef mVboMeshRef;
    gl::BatchRef mBatchRef;
    gl::GlslProgRef mShaderRef;
    std::vector<gl::VboMesh::Layout> bufferLayout;
    Eigen::MatrixXd mTV;
    Eigen::MatrixXi mTT;
    Eigen::MatrixXi mTF;
    Eigen::MatrixXd mV;
    Eigen::MatrixXd mC;
    Eigen::MatrixXi mF;
    Eigen::MatrixXi mE;
    Eigen::MatrixXd N_vertices;
    Eigen::MatrixXd N_faces;
    Eigen::MatrixXd N_corners;

  private:

    int tex_u;
    int tex_v;
    Eigen::Matrix<char, Eigen::Dynamic, 1> tex;

  };
}
