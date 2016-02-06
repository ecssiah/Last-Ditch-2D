#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

namespace ld
{

struct Input
{
  Input()
    : up(false),
      down(false),
      left(false),
      right(false),
      exit(false),
      activate(false),
      menu(false),
      sub_menu(false),
      mx(0),
      my(0)
  {}

  bool up, down;
  bool left, right;
  bool exit;
  bool activate;
  bool menu, sub_menu;
  Sint32 mx, my;
};

}

#endif /* INPUT_H */
