#ifndef RESOURCEINFO_H
#define RESOURCEINFO_H

#include <SDL2/SDL.h>
#include <string>

#include "ItemInfo.h"

namespace ld
{

struct ResourceInfo : public ItemInfo
{
  ResourceInfo() = default;
};

}

#endif /* RESOURCEINFO_H */
