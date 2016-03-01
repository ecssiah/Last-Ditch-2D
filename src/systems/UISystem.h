#ifndef UISYSTEM_H
#define UISYSTEM_H

#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <unordered_map>
#include <vector>

#include "../SDL_Interface.h"
#include "../components/UIElement.h"
#include "../components/ScalableElement.h"
#include "../components/User.h"
#include "TimeSystem.h"
#include "EntitySystem.h"
#include "InventoryUISystem.h"
#include "ProductionUISystem.h"
#include "ManagementUISystem.h"
#include "StatusUISystem.h"

namespace ld
{

class UISystem
{
  void setup_base();
  void setup_main();

  void update_base();
  void update_main();

  void handle_menu_activation();
  ScalableElement* find_scalable_element_at(Eigen::Vector2i& mouse_pos);

  Input& input;
  SDL_Interface& sdl_interface;
  TimeSystem& time_system;
  EntitySystem& entity_system;

  InventoryUISystem inventory_ui_system;
  ProductionUISystem production_ui_system;
  ManagementUISystem management_ui_system;
  StatusUISystem status_ui_system;

  bool base_active;
  bool main_active;

  User* active_user;

  UIElement date_and_time;

  std::vector<UIElement> base_ui_elements;
  std::vector<ScalableElement> base_scalable_elements;

  std::vector<UIElement> main_ui_elements;
  std::vector<ScalableElement> main_scalable_elements;

public:
  UISystem(
    SDL_Interface& sdl_interface, Input& input,
    TimeSystem& time_system, EntitySystem& entity_system);

  void update();
  void render();
};

}

#endif /* UISYSTEM_H */
