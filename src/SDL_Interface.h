#ifndef SDL_INTERFACE_H
#define SDL_INTERFACE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "constants/RenderConstants.h"

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
      SDL_CreateWindow(
	"Last Ditch", 100, 100, SCREEN_SIZE_X, SCREEN_SIZE_Y, SDL_WINDOW_SHOWN);
    renderer =
      SDL_CreateRenderer(
	window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    TTF_Init();

    auto img_flags(IMG_INIT_PNG);
    IMG_Init(img_flags);
  }


  void shutdown()
  {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
  }

  SDL_Window* window;
  SDL_Renderer* renderer;
};

}

#endif /* SDL_INTERFACE_H */
