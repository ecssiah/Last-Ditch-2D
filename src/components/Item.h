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
  Item()
    : name(std::string()),
      category(std::string()),
      contained(false),
      value(.1f),
      weight(1.f),
      volume(1.f),
      quality(.5f),
      durability(1.f),
      effects(),
      damages(),
      defenses()
  {}

  std::string name;
  std::string category;

  bool contained;

  float value;
  float weight;
  float volume;
  float quality;
  float durability;

  std::vector<Effect> effects;
  std::vector<Damage> damages;
  std::vector<Defense> defenses;
};

}

#endif /* ITEM_H */
