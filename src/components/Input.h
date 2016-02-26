#ifndef INPUT_H
#define INPUT_H

#include <eigen3/Eigen/Geometry>
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
      pause(false),
      activate(false),
      menu(false),
      sub_menu(false),
      mouse_pos(0, 0)
  {}

  bool up, down;
  bool left, right;
  bool exit;
  bool pause;
  bool activate;
  bool menu, sub_menu;

  Eigen::Vector2i mouse_pos;
};

}

#endif /* INPUT_H */
