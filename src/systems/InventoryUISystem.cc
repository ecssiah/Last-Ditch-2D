#include "InventoryUISystem.h"

#include <algorithm>
#include <eigen3/Eigen/Geometry>
#include <iostream>
#include <set>

#include "../components/Item.h"
#include "../constants/UIConstants.h"

using namespace Eigen;
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
    sort_buttons(),
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
    active_user->inventory.modified = false;
    update_inventory_list(active_user->inventory);
  }

  if (input.mouse_dragged)
  {
    auto element(find_scrollable_element_at(input.left_mouse_pressed_pos));

    if (element)
    {
      element->scrolled_offset += INVENTORY_SCROLL_RATE * input.mouse_drag_vector.y();
      element->scrolled_offset =
	std::max(-100, std::min(element->scrolled_offset, 0));

      update_inventory_list(active_user->inventory);
    }
  }
}


void InventoryUISystem::render()
{
  sdl_interface.render_scalable_element(menu_base);

  for (auto& element : sort_buttons)
    sdl_interface.render_scalable_element(element);

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

  setup_sort_buttons();

  ScrollableElement _inventory_list;
  _inventory_list.type = "list1";
  _inventory_list.texture = "inventory-list";
  _inventory_list.size = {400, 300};
  _inventory_list.pos = {menu_base.pos.x() + 10, menu_base.pos.y() + 80};

  scrollable_elements.push_back(_inventory_list);
  inventory_list = &scrollable_elements.back();

  update_inventory_list(active_user->inventory);
}


void InventoryUISystem::setup_sort_buttons()
{
  auto y_offset(30);
  auto x_offset(10);
  auto button_height(18);
  auto all_button_width(26);
  auto weapons_button_width(78);
  auto clothing_button_width(75);
  auto utility_button_width(74);
  auto production_button_width(92);

  ScalableElement sort_all_button;
  sort_all_button.type = "button1";
  sort_all_button.texture = "ui1";
  sort_all_button.text = "All";
  sort_all_button.text_texture = "inventory-sort-all-text";
  sort_all_button.size = {all_button_width, button_height};
  sort_all_button.pos = {menu_base.pos.x() + x_offset, menu_base.pos.y() + y_offset};

  sdl_interface.create_texture_from_text(
    sort_all_button.text, sort_all_button.text_texture, "jura-small");

  sort_buttons.push_back(sort_all_button);

  x_offset += sort_all_button.size.x() + 10;

  ScalableElement sort_weapons_button;
  sort_weapons_button.type = "button1";
  sort_weapons_button.texture = "ui1";
  sort_weapons_button.text = "Weapons";
  sort_weapons_button.text_texture = "inventory-sort-weapons-text";
  sort_weapons_button.size = {weapons_button_width, button_height};
  sort_weapons_button.pos = {menu_base.pos.x() + x_offset, menu_base.pos.y() + y_offset};

  sdl_interface.create_texture_from_text(
    sort_weapons_button.text, sort_weapons_button.text_texture, "jura-small");

  sort_buttons.push_back(sort_weapons_button);

  x_offset += sort_weapons_button.size.x() + 10;

  ScalableElement sort_clothing_button;
  sort_clothing_button.type = "button1";
  sort_clothing_button.texture = "ui1";
  sort_clothing_button.text = "Clothing";
  sort_clothing_button.text_texture = "inventory-sort-clothing-text";
  sort_clothing_button.size = {clothing_button_width, button_height};
  sort_clothing_button.pos = {menu_base.pos.x() + x_offset, menu_base.pos.y() + y_offset};

  sdl_interface.create_texture_from_text(
    sort_clothing_button.text, sort_clothing_button.text_texture, "jura-small");

  sort_buttons.push_back(sort_clothing_button);

  x_offset += sort_clothing_button.size.x() + 10;

  ScalableElement sort_utility_button;
  sort_utility_button.type = "button1";
  sort_utility_button.texture = "ui1";
  sort_utility_button.text = "Utility";
  sort_utility_button.text_texture = "inventory-sort-utility-text";
  sort_utility_button.size = {utility_button_width, button_height};
  sort_utility_button.pos = {menu_base.pos.x() + x_offset, menu_base.pos.y() + y_offset};

  sdl_interface.create_texture_from_text(
    sort_utility_button.text, sort_utility_button.text_texture, "jura-small");

  sort_buttons.push_back(sort_utility_button);

  x_offset += sort_utility_button.size.x() + 10;

  ScalableElement sort_production_button;
  sort_production_button.type = "button1";
  sort_production_button.texture = "ui1";
  sort_production_button.text = "Production";
  sort_production_button.text_texture = "inventory-sort-production-text";
  sort_production_button.size = {production_button_width, button_height};
  sort_production_button.pos = {menu_base.pos.x() + x_offset, menu_base.pos.y() + y_offset};

  sdl_interface.create_texture_from_text(
    sort_production_button.text, sort_production_button.text_texture, "jura-small");

  sort_buttons.push_back(sort_production_button);
}


void InventoryUISystem::generate_list_surfaces(
  Inventory& inventory, vector<SDL_Surface*>& element_surfaces)
{
  set<Item> unique_items;
  unordered_map<string, int> item_counts;

  for (auto item : inventory.items)
  {
    ++item_counts[item.type];
    unique_items.insert(item);
  }

  for (auto item : unique_items)
  {
    auto name(item.name);
    auto item_count(item_counts[item.type]);

    if (item_count != 1) name += " (" + to_string(item_count) + ")";

    SDL_Color color;
    color = {255, 255, 255};

    auto surface(sdl_interface.create_surface_from_text(name, "jura-small", color));

    element_surfaces.push_back(surface);
  }
}


void InventoryUISystem::update_inventory_list(Inventory& inventory)
{
  inventory_list->list_elements.clear();

  vector<SDL_Surface*> element_surfaces;
  generate_list_surfaces(inventory, element_surfaces);

  SDL_Surface* inventory_list_surface(
    sdl_interface.generate_surface(inventory_list->size.x(), inventory_list->size.y()));

  for (auto i(0); i < element_surfaces.size(); ++i)
  {
    SDL_Rect dst_rect;
    dst_rect.x = 10;
    dst_rect.y = element_surfaces[i]->h * i + inventory_list->scrolled_offset;

    SDL_BlitSurface(element_surfaces[i], nullptr, inventory_list_surface, &dst_rect);
  }

  if (sdl_interface.textures[inventory_list->texture] != nullptr)
    SDL_DestroyTexture(sdl_interface.textures[inventory_list->texture]);

  sdl_interface.textures[inventory_list->texture] =
    SDL_CreateTextureFromSurface(sdl_interface.renderer, inventory_list_surface);

  for (auto surface : element_surfaces)
    SDL_FreeSurface(surface);
}


ScrollableElement* InventoryUISystem::find_scrollable_element_at(Vector2i& screen_pos)
{
  for (auto& element : scrollable_elements)
  {
    auto hit(
      screen_pos.x() > element.pos.x() &&
      screen_pos.x() < element.pos.x() + element.size.x() &&
      screen_pos.y() > element.pos.y() &&
      screen_pos.y() < element.pos.y() + element.size.y());

    if (hit) return &element;
  }

  return nullptr;
}
