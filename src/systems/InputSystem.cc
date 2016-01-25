#include "InputSystem.h"

#include <iostream>
#include <SDL2/SDL.h>

using namespace ld;
using namespace std;

InputSystem::InputSystem(Input& input_)
  : input(input_)
{
  cout << "\nInput system ready" << endl;
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
    }
  }
}
