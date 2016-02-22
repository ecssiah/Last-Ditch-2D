#ifndef RESIZABLEELEMENT_H
#define RESIZABLEELEMENT_H

#include "StaticElement.h"

namespace ld
{

struct ResizableElement : public StaticElement
{
  ResizableElement()
    : StaticElement(),
      width(1.f),
      height(1.f),
      tl_texture(std::string()),
      tt_texture(std::string()),
      tr_texture(std::string()),
      rr_texture(std::string()),
      br_texture(std::string()),
      bb_texture(std::string()),
      bl_texture(std::string()),
      ll_texture(std::string())
  {}

  float width, height;

  std::string tl_texture;
  std::string tt_texture;
  std::string tr_texture;
  std::string rr_texture;
  std::string br_texture;
  std::string bb_texture;
  std::string bl_texture;
  std::string ll_texture;
};

}

#endif /* RESIZABLEELEMENT_H */
