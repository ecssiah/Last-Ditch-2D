#include "InputSystem.h"

#include <iostream>
#include <SDL2/SDL.h>

using namespace ld;
using namespace std;

InputSystem::InputSystem(Input& input_)
  : input(input_)
{
  cout << "Input system ready" << endl;
}


void InputSystem::update()
{
  SDL_Event e;

  while (SDL_PollEvent(&e))
  {
    switch (e.type)
    {
    case SDL_QUIT:
      input.exit = true;
      break;
    case SDL_KEYDOWN:
      switch (e.key.keysym.sym)
      {
      case SDLK_ESCAPE: input.exit = true; break;
      case SDLK_w: input.up = true; break;
      case SDLK_a: input.left = true; break;
      case SDLK_s: input.down = true; break;
      case SDLK_d: input.right = true; break;
      default: break;
      }
      break;
    case SDL_KEYUP:
      switch (e.key.keysym.sym)
      {
      case SDLK_w: input.up = false; break;
      case SDLK_a: input.left = false; break;
      case SDLK_s: input.down = false; break;
      case SDLK_d: input.right = false; break;
      default: break;
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      switch (e.button.button)
      {
      case SDL_BUTTON_LEFT: break;
      case SDL_BUTTON_RIGHT: break;
      default: break;
      }
      break;
    case SDL_MOUSEBUTTONUP:
      switch (e.button.button)
      {
      case SDL_BUTTON_LEFT: left_click(e.button.x, e.button.y); break;
      case SDL_BUTTON_RIGHT: input.sub_menu = true; break;
      default: break;
      }
      break;
    case SDL_MOUSEMOTION:
      break;
    default:
      break;
    }
  }
}


void InputSystem::left_click(Sint32 mx, Sint32 my)
{
  input.activate = true;
  input.mx = mx;
  input.my = my;
}
