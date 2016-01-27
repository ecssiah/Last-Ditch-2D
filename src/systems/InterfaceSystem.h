#ifndef INTERFACESYSTEM_H
#define INTERFACESYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

#include "../SDL_Interface.h"

namespace ld
{

class InterfaceSystem
{
  SDL_Interface& sdl_interface;

  SDL_Surface* test;
  SDL_Texture* test_tex;

  std::vector<TTF_Font*> fonts;

public:
  InterfaceSystem(SDL_Interface& sdl_interface);

  void update();
  void render();
};

}

#endif /* INTERFACESYSTEM_H */
