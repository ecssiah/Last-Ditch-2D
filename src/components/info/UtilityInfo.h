#ifndef UTILITYINFO_H
#define UTILITYINFO_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include "../Effect.h"
#include "ItemInfo.h"

namespace ld
{

struct UtilityInfo : public ItemInfo
{
  UtilityInfo() = default;

  std::vector<Effect> effects;
};

}

#endif /* UTILITYINFO_H */
