#ifndef STATICELEMENT_H
#define STATICELEMENT_H

#include "Entity.h"

namespace ld
{

struct StaticElement : public Entity
{
  StaticElement()
    : Entity(),
      clicked(false)
  {}

  bool clicked;
};

}

#endif /* STATICELEMENT_H */
