#ifndef BUTTON_H
#define BUTTON_H

#include "Scalable.h"

namespace ld
{

struct Button : public Scalable
{
  Button() = default;

  std::string text;
  std::string text_texture;

  bool clicked;
};

}

#endif /* BUTTON_H */
