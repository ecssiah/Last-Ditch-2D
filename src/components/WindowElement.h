#ifndef WINDOWELEMENT_H
#define WINDOWELEMENT_H

#include "ScalableElement.h"

namespace ld
{

struct WindowElement : public ScalableElement
{
  WindowElement() = default;

  std::string title;
};

}

#endif /* WINDOWELEMENT_H */
