#ifndef INVENTORYUISYSTEM_H
#define INVENTORYUISYSTEM_H

#include <unordered_map>
#include <vector>

#include "../components/ButtonElement.h"
#include "../components/Input.h"
#include "../components/Inventory.h"
#include "../components/SlotInfo.h"
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
  void setup_base();
  void setup_sort_buttons();
  void setup_preview_image();
  void setup_inventory_list();
  void setup_equipment_slots();

  void handle_dragged_event();
  void handle_wheel_event();
  void handle_activation_event();

  void update_preview_image();
  void update_inventory_list();

  Input& input;
  SDL_Interface& sdl_interface;

  EntitySystem& entity_system;
  InventorySystem& inventory_system;

  User& user;

  bool active;
  std::string active_category;

  unsigned active_slot_index;
  std::vector<SlotInfo> current_slots;

  WindowElement base_window;
  UIElement preview_image;
  ListElement inventory_list;

  std::vector<TextElement> equipment_slot_labels;
  std::vector<WindowElement> equipment_slot_windows;
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
