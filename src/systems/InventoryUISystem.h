#ifndef INVENTORYUISYSTEM_H
#define INVENTORYUISYSTEM_H

#include <vector>

#include "../components/Input.h"
#include "../components/Inventory.h"
#include "../components/ScalableElement.h"
#include "../components/ScrollableElement.h"
#include "../components/UIElement.h"
#include "../components/User.h"
#include "../systems/EntitySystem.h"
#include "../SDL_Interface.h"

namespace ld
{

class InventoryUISystem
{
  void setup();
  void update_inventory_list(Inventory& inventory);

  SDL_Interface& sdl_interface;
  Input& input;

  EntitySystem& entity_system;
  User* active_user;

  bool active;

  ScalableElement menu_base;
  ScrollableElement* inventory_list;

  std::vector<UIElement> elements;
  std::vector<ScalableElement> scalable_elements;
  std::vector<ScrollableElement> scrollable_elements;

public:
  InventoryUISystem(SDL_Interface& sdl_interface, Input& input, EntitySystem& entity_system);

  void update();
  void render();

  const bool& is_active() const { return active; }
  void set_active(bool _active) { active = _active; }

};

}

#endif /* INVENTORYUISYSTEM_H */