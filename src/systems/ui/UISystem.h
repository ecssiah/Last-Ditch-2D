#ifndef UISYSTEM_H
#define UISYSTEM_H

#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <unordered_map>
#include <vector>

#include "../../components/ui/Element.h"
#include "../../components/ui/Text.h"
#include "../../components/ui/Window.h"
#include "../../components/User.h"
#include "../../SDL_Interface.h"
#include "../EntitySystem.h"
#include "../TimeSystem.h"
#include "InventoryUISystem.h"
#include "ManagementUISystem.h"
#include "ProductionUISystem.h"
#include "StatusUISystem.h"

namespace ld
{

class UISystem
{
  void setup_base();
  void setup_main();

  void update_base();

  void render_base();
  void render_main();

  void handle_menu_event();
  void handle_activate_event();

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

  Text date_and_time;

  std::vector<Button> main_buttons;

public:
  UISystem(
    SDL_Interface& sdl_interface, Input& input,
    TimeSystem& time_system, EntitySystem& entity_system, InventorySystem& inventory_system);

  void update();
  void render();
};

}

#endif /* UISYSTEM_H */
