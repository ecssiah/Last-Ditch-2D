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
    if (e.type == SDL_QUIT) input.exit = true;
    if (e.type == SDL_KEYDOWN) input.exit = true;
  }
}
