#ifndef ITEM_H
#define ITEM_H

#include <functional>

#include "Entity.h"

namespace ld
{

struct Item : public Entity
{
  Item() = default;

  std::string name;
  std::string category;

  bool contained;

  float value;
  float quality;
  float durability;
  float weight;
  float volume;
};

}

#endif /* ITEM_H */
