/**
 *
 *
 */

#pragma once

#include "cinder/TriMesh.h"
#include <igl/igl_inline.h>
#include <igl/viewer/ViewerData.h>
#include <igl/AABB.h>

namespace cinder {
typedef std::shared_ptr<class IglMesh> IglMeshRef;
class IglMesh : public TriMesh {
  using TriMesh::TriMesh;
 public:
  IglMesh();
  IglMesh(const std::string str);
  IglMesh(Eigen::MatrixXd V, Eigen::MatrixXi F) {
    IglMesh();
    setMesh(V, F);
  };
  virtual ~IglMesh();
  bool loadMesh(const std::string str);
  void setMesh(Eigen::MatrixXd V, Eigen::MatrixXi F);
  void setV(Eigen::MatrixXd V) { data.set_vertices(V); };
  Eigen::MatrixXd getV() { return data.V; };
  Eigen::MatrixXi getF() { return data.F; };
  Eigen::MatrixXd* getVRef() { return &data.V; };
  Eigen::MatrixXi* getFRef() { return &data.F; };
  void setColor(Eigen::MatrixXd C) { data.set_colors(C); };
  igl::AABB<Eigen::MatrixXd, 3> getAABBTree() { return aabbTree; };

 public:
  igl::viewer::ViewerData data;

 private:
  igl::AABB<Eigen::MatrixXd, 3> aabbTree;

  TriMesh::Format fmt;

  Eigen::MatrixXf V_vbo;
  Eigen::MatrixXf V_normals_vbo;
  Eigen::MatrixXf V_ambient_vbo;
  Eigen::MatrixXf V_diffuse_vbo;
  Eigen::MatrixXf V_specular_vbo;
  Eigen::MatrixXf V_uv_vbo;
  Eigen::MatrixXf lines_V_vbo;
  Eigen::MatrixXf lines_V_colors_vbo;
  Eigen::MatrixXf points_V_vbo;
  Eigen::MatrixXf points_V_colors_vbo;

  int tex_u;
  int tex_v;
  Eigen::Matrix<char, Eigen::Dynamic, 1> tex;

  Eigen::Matrix<unsigned, Eigen::Dynamic, Eigen::Dynamic> F_vbo;
  Eigen::Matrix<unsigned, Eigen::Dynamic, Eigen::Dynamic> lines_F_vbo;
  Eigen::Matrix<unsigned, Eigen::Dynamic, Eigen::Dynamic> points_F_vbo;
};
}
