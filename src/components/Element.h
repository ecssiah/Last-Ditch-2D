#ifndef ELEMENT_H
#define ELEMENT_H

#include "Entity.h"

namespace ld
{

struct Element
{
  Element()
    : clicked(false),
      type(std::string()),
      text(std::string())
  {}

  bool clicked;
  std::string type;
  std::string text;
};

}

#endif /* ELEMENT_H */
