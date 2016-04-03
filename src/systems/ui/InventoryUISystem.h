#ifndef INVENTORYUISYSTEM_H
#define INVENTORYUISYSTEM_H

#include <unordered_map>
#include <vector>

#include "../../components/info/SlotInfo.h"
#include "../../components/Input.h"
#include "../../components/Inventory.h"
#include "../../components/User.h"
#include "../../components/ui/Button.h"
#include "../../components/ui/Element.h"
#include "../../components/ui/Window.h"
#include "../../SDL_Interface.h"
#include "../EntitySystem.h"
#include "../InventorySystem.h"

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

  bool active;
  std::string active_category;

  unsigned active_slot_index;
  std::vector<SlotInfo> current_slots;

  Window base_window;

  Element preview_image;
  List inventory_list;

  std::vector<Text> equipment_slot_labels;
  std::vector<Window> equipment_slot_windows;
  std::vector<Button> sort_buttons;

public:
  InventoryUISystem(
    Input& input, SDL_Interface& sdl_interface,
    EntitySystem& entity_system, InventorySystem& inventory_system);

  void update();
  void render();

  const bool& is_active() const { return active; }
  void set_active(bool _active) { active = _active; }

};

}

#endif /* INVENTORYUISYSTEM_H */
