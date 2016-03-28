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
  void setup_sort_buttons();

  void generate_list_surfaces(Inventory& inventory, std::vector<SDL_Surface*>& list_surfaces);
  void update_inventory_list(Inventory& inventory);
  ScrollableElement* find_scrollable_element_at(Eigen::Vector2i& screen_pos);
  bool element_hit_at(UIElement& element, Eigen::Vector2i& screen_pos);

  SDL_Interface& sdl_interface;
  Input& input;

  EntitySystem& entity_system;
  User* active_user;

  bool active;
  ItemCategory active_category;

  ScalableElement menu_base;
  ScrollableElement inventory_list;

  std::vector<ScalableElement> sort_buttons;

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
