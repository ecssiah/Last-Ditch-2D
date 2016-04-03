#ifndef USERINFO_H
#define USERINFO_H

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>

#include "AnimationInfo.h"

namespace ld
{

struct UserInfo
{
  UserInfo() = default;

  std::string name;
  std::string texture;

  std::unordered_map<std::string, AnimationInfo> animation_data;
};

}

#endif /* USERINFO_H */
