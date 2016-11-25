/** 
 *
 * 
 */

#pragma once

#include "cinder/TriMesh.h"
#include <igl/igl_inline.h>
#include <igl/viewer/ViewerData.h>

namespace cinder{
  typedef std::shared_ptr<class IglMesh>		IglMeshRef;
  class IglMesh : public TriMesh{
  public:
    IglMesh();
    IglMesh(const std::string str);
    IglMesh(Eigen::MatrixXd V, Eigen::MatrixXi F){setMesh(V,F);};
    virtual ~IglMesh();
    setMesh(Eigen::MatrixXd V, Eigen::MatrixXi F);
  private:
    igl::viewer::ViewerData data;
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
    Eigen::Matrix<char,Eigen::Dynamic,1> tex;

    Eigen::Matrix<unsigned, Eigen::Dynamic, Eigen::Dynamic> F_vbo;
    Eigen::Matrix<unsigned, Eigen::Dynamic, Eigen::Dynamic> lines_F_vbo;
    Eigen::Matrix<unsigned, Eigen::Dynamic, Eigen::Dynamic> points_F_vbo;
  };
}
