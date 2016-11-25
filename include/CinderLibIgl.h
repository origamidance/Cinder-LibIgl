/** 
 *
 * 
 */

#pragma once

#include "cinder/TriMesh.h"
#include <igl/viewer/ViewerData.h>

namespace cinder{
  typedef std::shared_ptr<class IglMesh>		IglMeshRef;
  class IglMesh : public TriMesh{
  public:
    IglMesh(){};
    IglMesh(Eigen::MatrixXd V, Eigen::MatrixXi F);
    ~IglMesh(){};
  private:
    igl::viewer::ViewerData data;
  };
}
