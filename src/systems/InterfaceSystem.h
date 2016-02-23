#ifndef INTERFACESYSTEM_H
#define INTERFACESYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <unordered_map>

#include "../SDL_Interface.h"
#include "../components/Element.h"
#include "../components/User.h"
#include "TimeSystem.h"
#include "EntitySystem.h"

namespace ld
{

class InterfaceSystem
{
  void update_date_and_time();
  void render_element_at(Element& element, int x, int y);

  Input& input;
  SDL_Interface& sdl_interface;
  TimeSystem& time_system;
  EntitySystem& entity_system;

  bool main_menu_active;
  bool inventory_menu_active;
  bool equipment_menu_active;
  bool production_menu_active;
  bool status_menu_active;

  User* active_user;

  Element date_and_time;

  std::unordered_map<std::string, TTF_Font*> fonts;
  std::unordered_map<std::string, SDL_Texture*> textures;

public:
  InterfaceSystem(
    SDL_Interface& sdl_interface, Input& input,
    TimeSystem& time_system, EntitySystem& entity_system);

  void update();
  void render();
};

}

#endif /* INTERFACESYSTEM_H */
