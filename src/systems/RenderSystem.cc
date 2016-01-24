#include "RenderSystem.h"

#include <iostream>

using namespace ld;
using namespace std;

RenderSystem::RenderSystem(SDL_Window* window_, MapSystem& map_system_)
  : window(window_),
    screen(SDL_GetWindowSurface(window)),
    map_system(map_system_)
{
  SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
  SDL_UpdateWindowSurface(window);

  cout << "Render system ready" << endl;
}


void RenderSystem::update()
{
}
