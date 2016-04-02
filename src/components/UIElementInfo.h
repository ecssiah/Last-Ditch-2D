#ifndef UIELEMENTINFO_H
#define UIELEMENTINFO_H

#include <string>

namespace ld
{

struct UIElementInfo
{
  UIElementInfo() = default;

  std::string texture;
  SDL_Rect clip_rect;
};

}

#endif /* UIELEMENTINFO_H */
