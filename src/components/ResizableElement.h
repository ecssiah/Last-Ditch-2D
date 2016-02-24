#ifndef RESIZABLEELEMENT_H
#define RESIZABLEELEMENT_H

#include <eigen3/Eigen/Geometry>

#include "UIElement.h"

namespace ld
{

struct ResizableElement : public UIElement
{
  ResizableElement()
    : UIElement(),
      size(60, 20)
  {
  }

  Eigen::Vector2i size;
};

}

#endif /* RESIZABLEELEMENT_H */
