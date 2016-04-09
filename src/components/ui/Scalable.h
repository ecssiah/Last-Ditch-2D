#ifndef SCALABLE_H
#define SCALABLE_H

#include "Element.h"

namespace ld
{

struct Scalable : public Element
{
  Scalable()
    : Element(),
      border(3)
  {}

  int border;
};

}

#endif /* SCALABLE_H */
