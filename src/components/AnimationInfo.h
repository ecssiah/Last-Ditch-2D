#ifndef ANIMATIONINFO_H
#define ANIMATIONINFO_H

#include <SDL2/SDL.h>

namespace ld
{

struct AnimationInfo
{
  AnimationInfo() = default;

  unsigned frames;

  SDL_Rect clip_rect;
};

}


#endif /* ANIMATIONINFO_H */
