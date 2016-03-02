#include "InventoryUISystem.h"

#include <iostream>

#include "../components/Item.h"
#include "../constants/UIConstants.h"

using namespace ld;
using namespace std;

InventoryUISystem::InventoryUISystem(
  SDL_Interface& _sdl_interface, Input& _input, EntitySystem& _entity_system
)
  : sdl_interface(_sdl_interface),
    input(_input),
    entity_system(_entity_system),
    active_user(_entity_system.get_active_user()),
    active(false),
    menu_base(),
    inventory_list(nullptr),
    elements(),
    scalable_elements()
{
  setup();
}


void InventoryUISystem::update()
{
  if (active_user->inventory.modified)
  {
    cout << "testing" << endl;
    update_inventory_list(active_user->inventory);

    active_user->inventory.modified = false;
  }
}


void InventoryUISystem::render()
{
  sdl_interface.render_scalable_element(menu_base);

  for (auto& element : elements)
    sdl_interface.render_element(element);

  for (auto& element : scalable_elements)
    sdl_interface.render_scalable_element(element);

  for (auto& element : scrollable_elements)
    sdl_interface.render_scrollable_element(element);
}


void InventoryUISystem::setup()
{
  menu_base.type = "backdrop1";
  menu_base.texture = "ui1";
  menu_base.size = {SUB_MENU_BASE_SIZE_X, SUB_MENU_BASE_SIZE_Y};
  menu_base.pos =
    {(SCREEN_SIZE_X - SUB_MENU_BASE_SIZE_X) / 2,
     (SCREEN_SIZE_Y - SUB_MENU_BASE_SIZE_Y) / 2};

  UIElement title;
  title.text = "Inventory";
  title.text_texture = "inventory-title-text";
  title.size = {200, 30};
  title.pos =
    {menu_base.pos.x() + (SUB_MENU_BASE_SIZE_X - title.size.x()) / 2,
     menu_base.pos.y()};

  sdl_interface.create_texture_from_text(title.text, title.text_texture, "jura-medium");

  elements.push_back(title);

  ScrollableElement _inventory_list;
  _inventory_list.type = "list1";
  _inventory_list.texture = "ui1";
  _inventory_list.size = {400, 600};
  _inventory_list.pos = {menu_base.pos.x() + 10, menu_base.pos.y() + 30};

  scrollable_elements.push_back(_inventory_list);
  inventory_list = &scrollable_elements.back();

  update_inventory_list(active_user->inventory);
}


void InventoryUISystem::update_inventory_list(Inventory& inventory)
{
  inventory_list->list_elements.clear();

  for (auto i(0); i < inventory.items.size(); ++i)
  {
    auto string(inventory.items[i].type);
    auto texture("inventory-list-" + to_string(i) + "-text");

    sdl_interface.create_texture_from_text(string, texture);
    inventory_list->list_elements.push_back({string, texture});

    cout << string << " " << texture << " ";
  }

  cout << endl;
}
