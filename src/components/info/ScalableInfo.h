#ifndef SCALABLEINFO_H
#define SCALABLEINFO_H

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>

namespace ld
{

struct ScalableInfo
{
  ScalableInfo() = default;

  std::string texture;

  std::unordered_map<std::string, SDL_Rect> clip_rects;
};

}

#endif /* SCALABLEINFO_H */
