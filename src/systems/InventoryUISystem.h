#ifndef INVENTORYUISYSTEM_H
#define INVENTORYUISYSTEM_H

#include <unordered_map>
#include <vector>

#include "../components/ButtonElement.h"
#include "../components/Input.h"
#include "../components/Inventory.h"
#include "../components/UIElement.h"
#include "../components/User.h"
#include "../components/WindowElement.h"
#include "../SDL_Interface.h"
#include "../systems/EntitySystem.h"
#include "../systems/InventorySystem.h"

namespace ld
{

class InventoryUISystem
{
  void setup();
  void setup_base();
  void setup_sort_buttons();
  void setup_inventory_list();
  void setup_inventory_info();
  void setup_equipment_slots();

  void handle_dragged_event();
  void handle_wheel_event();
  void handle_activation_event();

  void update_preview_texture();
  void update_inventory_list(Inventory& inventory);

  Input& input;
  SDL_Interface& sdl_interface;

  EntitySystem& entity_system;
  InventorySystem& inventory_system;

  User* active_user;

  bool active;
  unsigned active_slot_index;
  std::string active_category;

  std::vector<SlotInfo> current_slots;

  WindowElement menu_base;
  UIElement preview_image;
  ListElement inventory_list;

  std::vector<UIElement> elements;
  std::vector<ButtonElement> sort_buttons;

public:
  InventoryUISystem(
    SDL_Interface& sdl_interface, Input& input,
    EntitySystem& entity_system, InventorySystem& inventory_system);

  void update();
  void render();

  const bool& is_active() const { return active; }
  void set_active(bool _active) { active = _active; }

};

}

#endif /* INVENTORYUISYSTEM_H */
