#ifndef UISYSTEM_H
#define UISYSTEM_H

#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <unordered_map>
#include <vector>

#include "../components/ScalableElement.h"
#include "../components/TextElement.h"
#include "../components/UIElement.h"
#include "../components/User.h"
#include "../SDL_Interface.h"
#include "EntitySystem.h"
#include "InventoryUISystem.h"
#include "ManagementUISystem.h"
#include "ProductionUISystem.h"
#include "StatusUISystem.h"
#include "TimeSystem.h"

namespace ld
{

class UISystem
{
  void setup_base();
  void setup_main();

  void update_base();
  void update_main();

  void render_base();
  void render_main();

  void handle_menu_activation();
  ScalableElement* find_scalable_element_at(Eigen::Vector2i& screen_pos);

  Input& input;
  SDL_Interface& sdl_interface;
  TimeSystem& time_system;
  EntitySystem& entity_system;
  InventorySystem& inventory_system;

  InventoryUISystem inventory_ui_system;
  ProductionUISystem production_ui_system;
  ManagementUISystem management_ui_system;
  StatusUISystem status_ui_system;

  bool base_active;
  bool main_active;

  User* active_user;

  TextElement date_and_time;
  ScalableElement inventory_button;
  ScalableElement production_button;
  ScalableElement utility_button;
  ScalableElement status_button;

public:
  UISystem(
    SDL_Interface& sdl_interface, Input& input,
    TimeSystem& time_system, EntitySystem& entity_system, InventorySystem& inventory_system);

  void update();
  void render();
};

}

#endif /* UISYSTEM_H */
