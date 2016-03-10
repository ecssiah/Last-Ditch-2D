#ifndef LISTELEMENT_H
#define LISTELEMENT_H

#include <string>

#include "Item.h"

using namespace std;

namespace ld
{

struct ListElement
{
  ListElement()
    : string(std::string()),
      p_item(nullptr)
  {}

  ListElement(std::string _string, Item* _p_item)
    : string(_string),
      p_item(_p_item)
  {}

  std::string string;
  Item* p_item;
};

}

#endif /* LISTELEMENT_H */
