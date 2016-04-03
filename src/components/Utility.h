#ifndef UTILITY_H
#define UTILITY_H

#include "Effect.h"
#include "Item.h"

namespace ld
{

struct Utility : public Item
{
  Utility() = default;

  std::vector<Effect> effects;
};

}

#endif /* UTILITY_H */
