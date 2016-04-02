#ifndef USERINFO_H
#define USERINFO_H

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>

namespace ld
{

struct AnimationInfo
{
  AnimationInfo() = default;

  unsigned frames;
  SDL_Rect clip_rect;
};


struct UserInfo
{
  UserInfo() = default;

  std::string name;
  std::string texture;
  std::unordered_map<std::string, AnimationInfo> animations;
};

}

#endif /* USERINFO_H */
