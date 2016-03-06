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
      mouse_motion(false),
      mouse_dragged(false),
      left_mouse_pressed(false),
      right_mouse_pressed(false),
      mouse_drag_vector(0, 0),
      left_mouse_pressed_pos(0, 0),
      right_mouse_pressed_pos(0, 0),
      left_mouse_released_pos(0, 0),
      right_mouse_released_pos(0, 0)
  {}

  bool up, down;
  bool left, right;
  bool exit;
  bool pause;
  bool activate;
  bool menu, sub_menu;
  bool mouse_motion, mouse_dragged;
  bool left_mouse_pressed, right_mouse_pressed;

  Eigen::Vector2i mouse_drag_vector;
  Eigen::Vector2i left_mouse_pressed_pos, right_mouse_pressed_pos;
  Eigen::Vector2i left_mouse_released_pos, right_mouse_released_pos;
};

}

#endif /* INPUT_H */
