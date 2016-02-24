#ifndef INTERFACESYSTEM_H
#define INTERFACESYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <unordered_map>
#include <vector>

#include "../SDL_Interface.h"
#include "../components/UIElement.h"
#include "../components/ResizableElement.h"
#include "../components/User.h"
#include "TimeSystem.h"
#include "EntitySystem.h"

namespace ld
{

class InterfaceSystem
{
  void update_date_and_time();

  void render_element(UIElement& element);
  void render_resizable_element(ResizableElement& element);

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

  std::unordered_map<std::string, TTF_Font*> fonts;
  std::unordered_map<std::string, SDL_Texture*> textures;

  std::vector<UIElement> base_ui_elements;
  std::vector<ResizableElement> base_resizable_elements;

  UIElement* date_and_time;

public:
  InterfaceSystem(
    SDL_Interface& sdl_interface, Input& input,
    TimeSystem& time_system, EntitySystem& entity_system);
  ~InterfaceSystem();

  void update();
  void render();
};

}

#endif /* INTERFACESYSTEM_H */
