#ifndef INVENTORYUISYSTEM_H
#define INVENTORYUISYSTEM_H

#include <vector>

#include "../components/Input.h"
#include "../components/ScalableElement.h"
#include "../components/ScrollableElement.h"
#include "../components/UIElement.h"
#include "../systems/EntitySystem.h"
#include "../SDL_Interface.h"

namespace ld
{

class InventoryUISystem
{
  void setup();

  SDL_Interface& sdl_interface;
  Input& input;

  EntitySystem& entity_system;

  bool active;

  ScalableElement menu_base;
  ScrollableElement inventory_list;

  std::vector<UIElement> ui_elements;
  std::vector<ScalableElement> scalable_elements;

public:
  InventoryUISystem(SDL_Interface& sdl_interface, Input& input, EntitySystem& entity_system);

  void update();
  void render();

  const bool& is_active() const { return active; }
  void set_active(bool _active) { active = _active; }

};

}

#endif /* INVENTORYUISYSTEM_H */
