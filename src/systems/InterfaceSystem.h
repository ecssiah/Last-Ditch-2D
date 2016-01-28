#ifndef INTERFACESYSTEM_H
#define INTERFACESYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <map>

#include "../SDL_Interface.h"
#include "EntitySystem.h"

namespace ld
{

class InterfaceSystem
{
  SDL_Interface& sdl_interface;

  SDL_Texture* debug_text_texture;

  EntitySystem& entity_system;

  std::string debug_text;
  std::map<std::string, TTF_Font*> fonts;

public:
  InterfaceSystem(SDL_Interface& sdl_interface, EntitySystem& entity_system);

  void update();
  void render();
};

}

#endif /* INTERFACESYSTEM_H */
