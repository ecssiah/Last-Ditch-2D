#ifndef INTERFACESYSTEM_H
#define INTERFACESYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <map>

#include "../SDL_Interface.h"
#include "../components/User.h"
#include "TimeSystem.h"
#include "EntitySystem.h"

namespace ld
{

class InterfaceSystem
{
  void render_texture_at(std::string texture_name, int x, int y);

  SDL_Interface& sdl_interface;

  TimeSystem& time_system;
  EntitySystem& entity_system;

  User* active_user;

  std::map<std::string, TTF_Font*> fonts;
  std::map<std::string, SDL_Texture*> textures;

public:
  InterfaceSystem(
    SDL_Interface& sdl_interface, TimeSystem& time_system, EntitySystem& entity_system);

  void update();
  void render();
};

}

#endif /* INTERFACESYSTEM_H */
