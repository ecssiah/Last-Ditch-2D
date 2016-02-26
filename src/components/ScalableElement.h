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
      border(3)
  {}

  int border;
};

}

#endif /* SCALABLEELEMENT_H */
