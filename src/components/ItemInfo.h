#ifndef ITEMINFO_H
#define ITEMINFO_H

#include <SDL2/SDL.h>
#include <string>

namespace ld
{

struct ItemInfo
{
  ItemInfo() = default;

  std::string name;
  std::string category;
  std::string texture;

  float value;
  float quality;
  float weight;
  float volume;

  SDL_Rect clip_rect;
};

}

#endif /* ITEMINFO_H */
