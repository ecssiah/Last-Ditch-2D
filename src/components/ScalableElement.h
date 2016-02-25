#ifndef SCALABLEELEMENT_H
#define SCALABLEELEMENT_H

#include <eigen3/Eigen/Geometry>

#include "UIElement.h"

namespace ld
{

struct ScalableElement : public UIElement
{
  ScalableElement()
    : UIElement(),
      size(200, 40),
      border(3)
  {
  }

  Eigen::Vector2i size;
  int border;
};

}

#endif /* SCALABLEELEMENT_H */
