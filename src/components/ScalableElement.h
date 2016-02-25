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
      size(60, 20)
  {
  }

  Eigen::Vector2i size;
};

}

#endif /* SCALABLEELEMENT_H */
