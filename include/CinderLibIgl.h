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
    igl::viewer::ViewerData test;
  };
}
