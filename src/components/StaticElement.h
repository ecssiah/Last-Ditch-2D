#ifndef STATICELEMENT_H
#define STATICELEMENT_H

#include "Entity.h"

namespace ld
{

struct StaticElement : public Entity
{
  StaticElement()
    : Entity(),
      clicked(false),
      text(std::string())
  {}

  bool clicked;
  std::string text;
};

}

#endif /* STATICELEMENT_H */
