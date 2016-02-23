#ifndef STATICELEMENT_H
#define STATICELEMENT_H

#include "Entity.h"

namespace ld
{

enum ElementType
{
  STATIC,
  RESIZABLE
}


struct StaticElement : public Entity
{
  StaticElement()
    : Entity(),
      clicked(false),
      element_type(STATIC),
      text(std::string())
  {}

  bool clicked;
  ElementType element_type;
  std::string text;
};

}

#endif /* STATICELEMENT_H */
