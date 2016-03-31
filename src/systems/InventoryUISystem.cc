#include "InventoryUISystem.h"

#include <algorithm>
#include <eigen3/Eigen/Geometry>
#include <functional>
#include <iostream>
#include <set>

#include "../components/Item.h"
#include "../constants/UIConstants.h"
#include "../Utils.h"

using namespace Eigen;
using namespace ld;
using namespace std;
using namespace Utils;

InventoryUISystem::InventoryUISystem(
  SDL_Interface& _sdl_interface, Input& _input,
  EntitySystem& _entity_system, InventorySystem& _inventory_system
)
  : sdl_interface(_sdl_interface),
    input(_input),
    entity_system(_entity_system),
    inventory_system(_inventory_system),
    active_user(_entity_system.get_active_user()),
    active(false),
    active_category(ALL),
    active_slot_index(0),
    current_slots(),
    inventory_list(),
    sort_buttons(),
    elements(),
    scalable_elements(),
    p_scrollable_elements()
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
    if (element_hit_at(inventory_list, input.left_mouse_pressed_pos))
    {
      inventory_list.scrolled_offset +=
	INVENTORY_MOUSE_SCROLL_RATE * input.mouse_drag_vector.y();
      inventory_list.scrolled_offset = clamp(inventory_list.scrolled_offset, -100, 0);

      update_inventory_list(active_user->inventory);

      return;
    }

    auto element(find_scrollable_element_at(input.left_mouse_pressed_pos));

    if (element)
    {
      element->scrolled_offset +=
	INVENTORY_MOUSE_SCROLL_RATE * input.mouse_drag_vector.y();
      element->scrolled_offset = clamp(element->scrolled_offset, -100, 0);

      update_inventory_list(active_user->inventory);

      return;
    }
  }

  if (input.mouse_wheel)
  {
    inventory_list.scrolled_offset +=
      INVENTORY_WHEEL_SCROLL_RATE * input.mouse_wheel_vector.y();
    inventory_list.scrolled_offset = clamp(inventory_list.scrolled_offset, -100, 0);

    update_inventory_list(active_user->inventory);
  }

  if (input.activate)
  {
    auto p_sort_element(find_scalable_element_at(input.left_mouse_released_pos));

    if (p_sort_element)
    {
      input.activate = false;

      if (p_sort_element->text == "All")
	active_category = ALL;
      else if (p_sort_element->text == "Weapons")
	active_category = WEAPONS;
      else if (p_sort_element->text == "Clothing")
	active_category = CLOTHING;
      else if (p_sort_element->text == "Utility")
	active_category = UTILITY;
      else if (p_sort_element->text == "Production")
	active_category = PRODUCTION;

      update_inventory_list(active_user->inventory);

      return;
    }

    auto p_inventory_list(find_scrollable_element_at(input.left_mouse_released_pos));

    if (p_inventory_list)
    {
      input.activate = false;

      auto offset(
	input.left_mouse_released_pos.y() - p_inventory_list->pos.y() -
	p_inventory_list->scrolled_offset);

      active_slot_index = offset / MENU_BUTTON_SIZE_Y;

      update_inventory_list(active_user->inventory);

      return;
    }
  }
}


void InventoryUISystem::render()
{
  sdl_interface.render_scalable_element(menu_base);
  sdl_interface.render_scrollable_element(inventory_list);

  for (auto& element : sort_buttons)
    sdl_interface.render_scalable_element(element);

  for (auto& element : elements)
    sdl_interface.render_element(element);

  for (auto& element : scalable_elements)
    sdl_interface.render_scalable_element(element);

  for (auto element : p_scrollable_elements)
    sdl_interface.render_scrollable_element(*element);
}


void InventoryUISystem::setup()
{
  menu_base.type = "backdrop1";
  menu_base.texture = "ui1";
  menu_base.size = {MENU_BASE_SIZE_X, MENU_BASE_SIZE_Y};
  menu_base.pos =
    {(SCREEN_SIZE_X - MENU_BASE_SIZE_X) / 2,
     (SCREEN_SIZE_Y - MENU_BASE_SIZE_Y) / 2};

  UIElement title;
  title.text = "Inventory";
  title.text_texture = "inventory-title-text";
  title.size = {200, 30};
  title.pos =
    {menu_base.pos.x() + (MENU_BASE_SIZE_X - title.size.x()) / 2,
     menu_base.pos.y()};

  sdl_interface.create_texture_from_text(title.text, title.text_texture, "jura-medium");

  elements.push_back(title);

  setup_sort_buttons();

  inventory_list.type = "list1";
  inventory_list.texture = "inventory-list";
  inventory_list.size = {400, 300};
  inventory_list.pos = {menu_base.pos.x() + 8, menu_base.pos.y() + 58};

  update_inventory_list(active_user->inventory);

  p_scrollable_elements.push_back(&inventory_list);

  ScalableElement inventory_preview;
  inventory_preview.type = "window1";
  inventory_preview.texture = "ui1";
  inventory_preview.border = 1;
  inventory_preview.size = {100, 100};
  inventory_preview.pos = {menu_base.pos.x() + 440, menu_base.pos.y() + 42};

  scalable_elements.push_back(inventory_preview);
}


void InventoryUISystem::setup_sort_buttons()
{
  auto y_offset(30);
  auto x_offset(10);
  auto button_height(18);
  auto all_button_width(28);
  auto weapons_button_width(78);
  auto clothing_button_width(73);
  auto utility_button_width(52);
  auto production_button_width(92);

  ScalableElement sort_all_button;
  sort_all_button.type = "button1";
  sort_all_button.texture = "ui1";
  sort_all_button.text = "All";
  sort_all_button.text_texture = "inventory-sort-all-text";
  sort_all_button.border = 4;
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
  sort_weapons_button.border = 4;
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
  sort_clothing_button.border = 4;
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
  sort_utility_button.border = 4;
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
  sort_production_button.border = 4;
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
  unordered_map<string, unsigned> item_counts;

  for (auto& item : inventory.items)
  {
    ++item_counts[item.type];

    if (active_category == ALL || item.category == active_category)
      unique_items.insert(item);
  }

  current_slots.clear();
  vector<Item> items(unique_items.begin(), unique_items.end());

  for (auto i(0); i < items.size(); ++i)
  {
    auto& item(items[i]);
    auto& name(item.name);
    auto& item_count(item_counts[item.type]);

    if (item_count != 1) name += " (" + to_string(item_count) + ")";

    SDL_Color color;

    if (i == active_slot_index)
      color = {255, 255, 255};
    else
      color = {200, 180, 200};

    auto surface(sdl_interface.create_surface_from_text(name, "jura-small", color));
    element_surfaces.push_back(surface);

    current_slots.push_back({(unsigned)i, item_count, item.type});
  }
}


void InventoryUISystem::update_active_slot_preview_image()
{


}


void InventoryUISystem::update_inventory_list(Inventory& inventory)
{
  inventory_list.list_elements.clear();

  vector<SDL_Surface*> element_surfaces;
  generate_list_surfaces(inventory, element_surfaces);

  SDL_Surface* inventory_list_surface(
    sdl_interface.generate_surface(inventory_list.size.x(), inventory_list.size.y()));

  for (auto i(0); i < element_surfaces.size(); ++i)
  {
    SDL_Rect dst_rect;
    dst_rect.x = 10;
    dst_rect.y = element_surfaces[i]->h * i + inventory_list.scrolled_offset;

    SDL_BlitSurface(element_surfaces[i], nullptr, inventory_list_surface, &dst_rect);
  }

  if (sdl_interface.textures[inventory_list.texture] != nullptr)
    SDL_DestroyTexture(sdl_interface.textures[inventory_list.texture]);

  sdl_interface.textures[inventory_list.texture] =
    SDL_CreateTextureFromSurface(sdl_interface.renderer, inventory_list_surface);

  for (auto surface : element_surfaces) SDL_FreeSurface(surface);

  update_active_slot_preview_image();
}


bool InventoryUISystem::element_hit_at(UIElement& element, Vector2i& screen_pos)
{
  auto hit(
    screen_pos.x() > element.pos.x() &&
    screen_pos.x() < element.pos.x() + element.size.x() &&
    screen_pos.y() > element.pos.y() &&
    screen_pos.y() < element.pos.y() + element.size.y());

  if (hit) return true;

  return false;
}


ScrollableElement* InventoryUISystem::find_scrollable_element_at(Vector2i& screen_pos)
{
  for (auto element : p_scrollable_elements)
    if (element_hit_at(*element, screen_pos)) return element;

  return nullptr;
}


ScalableElement* InventoryUISystem::find_scalable_element_at(Vector2i& screen_pos)
{
  for (auto& element : sort_buttons)
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
