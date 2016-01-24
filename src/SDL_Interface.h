#ifndef SDL_INTERFACE_H
#define SDL_INTERFACE_H

#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

namespace ld
{

struct SDL_Interface
{
  SDL_Interface()
    : window(nullptr),
      renderer(nullptr)
  {
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
      cout << "SDL_Init error: " << SDL_GetError() << endl;

    window =
      SDL_CreateWindow("Last Ditch", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
    renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  }


  void shutdown()
  {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();
  }

  SDL_Window* window;
  SDL_Renderer* renderer;
};

}

#endif /* SDL_INTERFACE_H */
