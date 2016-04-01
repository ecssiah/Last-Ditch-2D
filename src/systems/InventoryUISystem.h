#ifndef INVENTORYUISYSTEM_H
#define INVENTORYUISYSTEM_H

#include <unordered_map>
#include <vector>

#include "../components/Input.h"
#include "../components/Inventory.h"
#include "../components/ScalableElement.h"
#include "../components/ScrollableElement.h"
#include "../components/UIElement.h"
#include "../components/User.h"
#include "../systems/EntitySystem.h"
#include "../systems/InventorySystem.h"
#include "../SDL_Interface.h"

namespace ld
{

struct SlotInfo
{
  SlotInfo(unsigned _index, unsigned _count, std::string _type)
    : index(_index),
      count(_count),
      type(_type)
  {}

  unsigned index;
  unsigned count;
  std::string type;
};

class InventoryUISystem
{
  void setup();
  void setup_base();
  void setup_sort_buttons();
  void setup_inventory_list();
  void setup_inventory_info();
  void setup_equipment_slots();

  void generate_list_surfaces(Inventory& inventory, std::vector<SDL_Surface*>& list_surfaces);
  void update_inventory_list(Inventory& inventory);
  void update_active_slot_preview_image();
  ScalableElement* find_scalable_element_at(Eigen::Vector2i& screen_pos);
  ScrollableElement* find_scrollable_element_at(Eigen::Vector2i& screen_pos);
  bool element_hit_at(UIElement& element, Eigen::Vector2i& screen_pos);

  SDL_Interface& sdl_interface;
  Input& input;

  EntitySystem& entity_system;
  InventorySystem& inventory_system;
  User* active_user;

  bool active;
  ItemCategory active_category;

  unsigned active_slot_index;
  std::vector<SlotInfo> current_slots;

  ScalableElement menu_base;
  ScalableElement active_item_preview_image;
  ScrollableElement inventory_list;

  std::vector<ScalableElement> sort_buttons;

  std::vector<UIElement> elements;
  std::vector<ScalableElement> scalable_elements;
  std::vector<ScrollableElement*> p_scrollable_elements;

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
