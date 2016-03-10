#include "InputSystem.h"

#include <iostream>
#include <SDL2/SDL.h>

using namespace ld;
using namespace std;

InputSystem::InputSystem(Input& input_)
  : input(input_)
{
  cout << "InputSystem ready" << endl;
}


void InputSystem::update()
{
  input.mouse_motion = false;
  input.mouse_dragged = false;
  input.mouse_drag_vector = {0, 0};
  input.mouse_wheel = false;
  input.mouse_wheel_vector = {0, 0};

  for (SDL_Event e; SDL_PollEvent(&e); )
  {
    switch (e.type)
    {
    case SDL_QUIT:
      input.exit = true;
      break;
    case SDL_KEYDOWN:
      switch (e.key.keysym.sym)
      {
      case SDLK_w: input.up = true; break;
      case SDLK_a: input.left = true; break;
      case SDLK_s: input.down = true; break;
      case SDLK_d: input.right = true; break;
      case SDLK_ESCAPE: input.exit = true; break;
      default:
	break;
      }
      break;
    case SDL_KEYUP:
      switch (e.key.keysym.sym)
      {
      case SDLK_w: input.up = false; break;
      case SDLK_a: input.left = false; break;
      case SDLK_s: input.down = false; break;
      case SDLK_d: input.right = false; break;
      case SDLK_TAB: input.menu = true; break;
      case SDLK_SPACE: input.pause = !input.pause; break;
      default:
	break;
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      switch (e.button.button)
      {
      case SDL_BUTTON_LEFT:
	input.left_mouse_pressed = true;
	input.left_mouse_pressed_pos = {e.button.x, e.button.y};
	break;
      case SDL_BUTTON_RIGHT:
	input.right_mouse_pressed = true;
	input.right_mouse_pressed_pos = {e.button.x, e.button.y};
	break;
      default: break;
      }
      break;
    case SDL_MOUSEBUTTONUP:
      switch (e.button.button)
      {
      case SDL_BUTTON_LEFT:
	input.activate = true;
	input.left_mouse_pressed = false;
	input.left_mouse_released_pos = {e.button.x, e.button.y};
	break;
      case SDL_BUTTON_RIGHT:
	input.right_mouse_pressed = false;
	input.right_mouse_released_pos = {e.button.x, e.button.y};
	break;
      default:
	break;
      }
      break;
    case SDL_MOUSEMOTION:
      input.mouse_motion = true;
      input.mouse_drag_vector = {e.motion.xrel, e.motion.yrel};
      break;
    case SDL_MOUSEWHEEL:
      input.mouse_wheel = true;
      input.mouse_wheel_vector = {e.wheel.x, e.wheel.y};
      break;
    default:
      break;
    }
  }

  if (input.mouse_motion && input.left_mouse_pressed)
    input.mouse_dragged = true;
}
