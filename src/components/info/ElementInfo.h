#ifndef ELEMENTINFO_H
#define ELEMENTINFO_H

#include <string>

namespace ld
{

struct ElementInfo
{
  ElementInfo() = default;

  std::string texture;

  SDL_Rect clip_rect;
};

}

#endif /* ELEMENTINFO_H */
