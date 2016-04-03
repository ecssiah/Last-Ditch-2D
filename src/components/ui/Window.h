#ifndef WINDOW_H
#define WINDOW_H

#include "Element.h"

namespace ld
{

struct Window : public Element
{
  Window()
    : border(3)
  {}

  int border;
};

}

#endif /* WINDOW_H */
