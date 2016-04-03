#ifndef SCALABLE_H
#define SCALABLE_H

#include "Element.h"

namespace ld
{

struct Scalable : public Element
{
  Scalable()
    : border(3)
  {}

  int border;
};

}

#endif /* SCALABLE_H */
