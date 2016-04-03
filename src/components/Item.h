#ifndef ITEM_H
#define ITEM_H

#include <vector>

#include "Entity.h"
#include "Effect.h"
#include "Damage.h"
#include "Defense.h"

namespace ld
{

struct Item : public Entity
{
  Item() = default;

  std::string name;
  std::string category;

  bool contained;

  float value;
  float weight;
  float volume;
  float quality;
  float durability;

  std::vector<Effect> effects;
  std::vector<Damage> damage;
  std::vector<Defense> defense;
};

}

#endif /* ITEM_H */
