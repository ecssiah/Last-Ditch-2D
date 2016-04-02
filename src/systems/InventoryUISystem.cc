#include "InventoryUISystem.h"

#include <algorithm>
#include <cassert>
#include <eigen3/Eigen/Geometry>
#include <functional>
#include <iostream>
#include <set>
#include <yaml-cpp/yaml.h>

#include "../components/Item.h"
#include "../constants/UIConstants.h"
#include "../Utils.h"

using namespace Eigen;
using namespace ld;
using namespace std;
using namespace Utils;

InventoryUISystem::InventoryUISystem(
  Input& _input, SDL_Interface& _sdl_interface,
  EntitySystem& _entity_system, InventorySystem& _inventory_system
)
  : input(_input),
    sdl_interface(_sdl_interface),
    entity_system(_entity_system),
    inventory_system(_inventory_system),
    active_user(_entity_system.get_active_user()),
    active(false),
    active_category("All"),
    active_slot_index(0)
{
  setup();
}


void InventoryUISystem::update()
{
  if (active_user->inventory.modified) cleanup_modifications();

  if (input.mouse_dragged) handle_dragged_event();
  if (input.mouse_wheel) handle_wheel_event();
  if (input.activate) handle_activation_event();
}


void InventoryUISystem::cleanup_modifications()
{
  update_inventory_list(active_user->inventory);

  active_user->inventory.modified = false;
}


void InventoryUISystem::handle_dragged_event()
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


void InventoryUISystem::handle_wheel_event()
{
  inventory_list.scrolled_offset +=
    INVENTORY_WHEEL_SCROLL_RATE * input.mouse_wheel_vector.y();
  inventory_list.scrolled_offset = clamp(inventory_list.scrolled_offset, -100, 0);

  update_inventory_list(active_user->inventory);
}


void InventoryUISystem::handle_activation_event()
{
  auto p_sort_element(find_scalable_element_at(input.left_mouse_released_pos));

  if (p_sort_element)
  {
    input.activate = false;

    p_sort_element->text = active_category;

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


void InventoryUISystem::render()
{
  sdl_interface.render_window_element(menu_base);
  sdl_interface.render_list_element(inventory_list);

  for (auto& element : sort_buttons) sdl_interface.render_button_element(element);
  for (auto& element : ui_elements) sdl_interface.render_ui_element(element);

  sdl_interface.render_ui_element(preview_image);
}


void InventoryUISystem::setup()
{
  setup_base();
  setup_sort_buttons();
  setup_inventory_list();
  setup_inventory_info();
  setup_equipment_slots();
}


void InventoryUISystem::setup_base()
{
  menu_base.type = "window1";
  menu_base.texture = "ui1";
  menu_base.size = {MENU_BASE_SIZE_X, MENU_BASE_SIZE_Y};
  menu_base.pos =
    {(SCREEN_SIZE_X - MENU_BASE_SIZE_X) / 2,
     (SCREEN_SIZE_Y - MENU_BASE_SIZE_Y) / 2};

  TextElement title;
  title.text = "Inventory";
  title.text_texture = "inventory-title";
  title.size = {200, 36};
  title.pos =
    {menu_base.pos.x() + (MENU_BASE_SIZE_X - title.size.x()) / 2,
     menu_base.pos.y()};

  sdl_interface.create_texture_from_text(title.text, title.text_texture, "jura-medium");

  ui_elements.push_back(title);
}


void InventoryUISystem::setup_sort_buttons()
{
  auto y_offset(180);
  auto x_offset(16);
  auto x_spacing(4);
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

  x_offset += sort_all_button.size.x() + x_spacing;

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

  x_offset += sort_weapons_button.size.x() + x_spacing;

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

  x_offset += sort_clothing_button.size.x() + x_spacing;

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

  x_offset += sort_utility_button.size.x() + x_spacing;

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


void InventoryUISystem::setup_inventory_list()
{
  inventory_list.type = "list1";
  inventory_list.texture = "inventory-list";
  inventory_list.size = {360, 300};
  inventory_list.pos = {menu_base.pos.x() + 16, menu_base.pos.y() + 200};

  update_inventory_list(active_user->inventory);
}


void InventoryUISystem::setup_inventory_info()
{
  auto x(menu_base.pos.x() + 16);
  auto y(menu_base.pos.y() + 40);

  ScalableElement inventory_preview;
  inventory_preview.type = "window1";
  inventory_preview.texture = "ui1";
  inventory_preview.border = 1;
  inventory_preview.size = {HALF_UNIT + 10, HALF_UNIT + 10};
  inventory_preview.pos = {x, y};

  active_item_preview_image.type = "image1";
  active_item_preview_image.texture = "items1";
  active_item_preview_image.size = {HALF_UNIT, HALF_UNIT};
  active_item_preview_image.pos = {x + 5, y + 5};
}


void InventoryUISystem::setup_equipment_slots()
{
  auto x_offset(440);
  auto y_offset(40);
  auto x_size(210);
  auto y_size(18);
  auto y_spacing(20);

  UIElement head_slot_label;
  head_slot_label.text = "Head";
  head_slot_label.text_texture = "inventory-head-slot-label-texture";
  head_slot_label.size = {60, 20};
  head_slot_label.pos = {menu_base.pos.x() + x_offset - 60, menu_base.pos.y() + y_offset};

  sdl_interface.create_texture_from_text(
    head_slot_label.text, head_slot_label.text_texture, "jura-small");

  ScalableElement head_slot_window;
  head_slot_window.type = "window1";
  head_slot_window.texture = "ui1";
  head_slot_window.border = 1;
  head_slot_window.size = {x_size, y_size};
  head_slot_window.pos = {menu_base.pos.x() + x_offset, menu_base.pos.y() + y_offset};

  y_offset += y_spacing;

  UIElement torso_slot_label;
  torso_slot_label.text = "Torso";
  torso_slot_label.text_texture = "inventory-torso-slot-label-texture";
  torso_slot_label.size = {60, 20};
  torso_slot_label.pos = {menu_base.pos.x() + x_offset - 60, menu_base.pos.y() + y_offset};

  sdl_interface.create_texture_from_text(
    torso_slot_label.text, torso_slot_label.text_texture, "jura-small");

  ScalableElement torso_slot_window;
  torso_slot_window.type = "window1";
  torso_slot_window.texture = "ui1";
  torso_slot_window.border = 1;
  torso_slot_window.size = {x_size, y_size};
  torso_slot_window.pos = {menu_base.pos.x() + x_offset, menu_base.pos.y() + y_offset};

  y_offset += y_spacing;

  UIElement back_slot_label;
  back_slot_label.text = "Back";
  back_slot_label.text_texture = "inventory-back-slot-label-texture";
  back_slot_label.size = {60, 20};
  back_slot_label.pos = {menu_base.pos.x() + x_offset - 60, menu_base.pos.y() + y_offset};

  sdl_interface.create_texture_from_text(
    back_slot_label.text, back_slot_label.text_texture, "jura-small");

  ScalableElement back_slot_window;
  back_slot_window.type = "window1";
  back_slot_window.texture = "ui1";
  back_slot_window.border = 1;
  back_slot_window.size = {x_size, y_size};
  back_slot_window.pos = {menu_base.pos.x() + x_offset, menu_base.pos.y() + y_offset};

  y_offset += y_spacing;

  UIElement larm_slot_label;
  larm_slot_label.text = "L Arm";
  larm_slot_label.text_texture = "inventory-larm-slot-label-texture";
  larm_slot_label.size = {60, 20};
  larm_slot_label.pos = {menu_base.pos.x() + x_offset - 60, menu_base.pos.y() + y_offset};

  sdl_interface.create_texture_from_text(
    larm_slot_label.text, larm_slot_label.text_texture, "jura-small");

  ScalableElement larm_slot_window;
  larm_slot_window.type = "window1";
  larm_slot_window.texture = "ui1";
  larm_slot_window.border = 1;
  larm_slot_window.size = {x_size, y_size};
  larm_slot_window.pos = {menu_base.pos.x() + x_offset, menu_base.pos.y() + y_offset};

  y_offset += y_spacing;

  UIElement rarm_slot_label;
  rarm_slot_label.text = "R Arm";
  rarm_slot_label.text_texture = "inventory-rarm-slot-label-texture";
  rarm_slot_label.size = {60, 20};
  rarm_slot_label.pos = {menu_base.pos.x() + x_offset - 60, menu_base.pos.y() + y_offset};

  sdl_interface.create_texture_from_text(
    rarm_slot_label.text, rarm_slot_label.text_texture, "jura-small");

  ScalableElement rarm_slot_window;
  rarm_slot_window.type = "window1";
  rarm_slot_window.texture = "ui1";
  rarm_slot_window.border = 1;
  rarm_slot_window.size = {x_size, y_size};
  rarm_slot_window.pos = {menu_base.pos.x() + x_offset, menu_base.pos.y() + y_offset};

  y_offset += y_spacing;

  UIElement lleg_slot_label;
  lleg_slot_label.text = "L Leg";
  lleg_slot_label.text_texture = "inventory-lleg-slot-label-texture";
  lleg_slot_label.size = {60, 20};
  lleg_slot_label.pos = {menu_base.pos.x() + x_offset - 60, menu_base.pos.y() + y_offset};

  sdl_interface.create_texture_from_text(
    lleg_slot_label.text, lleg_slot_label.text_texture, "jura-small");

  ScalableElement lleg_slot_window;
  lleg_slot_window.type = "window1";
  lleg_slot_window.texture = "ui1";
  lleg_slot_window.border = 1;
  lleg_slot_window.size = {x_size, y_size};
  lleg_slot_window.pos = {menu_base.pos.x() + x_offset, menu_base.pos.y() + y_offset};

  y_offset += y_spacing;

  UIElement rleg_slot_label;
  rleg_slot_label.text = "R Leg";
  rleg_slot_label.text_texture = "inventory-rleg-slot-label-texture";
  rleg_slot_label.size = {60, 20};
  rleg_slot_label.pos = {menu_base.pos.x() + x_offset - 60, menu_base.pos.y() + y_offset};

  sdl_interface.create_texture_from_text(
    rleg_slot_label.text, rleg_slot_label.text_texture, "jura-small");

  ScalableElement rleg_slot_window;
  rleg_slot_window.type = "window1";
  rleg_slot_window.texture = "ui1";
  rleg_slot_window.border = 1;
  rleg_slot_window.size = {x_size, y_size};
  rleg_slot_window.pos = {menu_base.pos.x() + x_offset, menu_base.pos.y() + y_offset};

  y_offset += y_spacing;

  UIElement lhand_slot_label;
  lhand_slot_label.text = "L Hand";
  lhand_slot_label.text_texture = "inventory-lhand-slot-label-texture";
  lhand_slot_label.size = {60, 20};
  lhand_slot_label.pos = {menu_base.pos.x() + x_offset - 60, menu_base.pos.y() + y_offset};

  sdl_interface.create_texture_from_text(
    lhand_slot_label.text, lhand_slot_label.text_texture, "jura-small");

  ScalableElement lhand_slot_window;
  lhand_slot_window.type = "window1";
  lhand_slot_window.texture = "ui1";
  lhand_slot_window.border = 1;
  lhand_slot_window.size = {x_size, y_size};
  lhand_slot_window.pos = {menu_base.pos.x() + x_offset, menu_base.pos.y() + y_offset};

  y_offset += y_spacing;

  UIElement rhand_slot_label;
  rhand_slot_label.text = "R Hand";
  rhand_slot_label.text_texture = "inventory-rhand-slot-label-texture";
  rhand_slot_label.size = {60, 20};
  rhand_slot_label.pos = {menu_base.pos.x() + x_offset - 60, menu_base.pos.y() + y_offset};

  sdl_interface.create_texture_from_text(
    rhand_slot_label.text, rhand_slot_label.text_texture, "jura-small");

  ScalableElement rhand_slot_window;
  rhand_slot_window.type = "window1";
  rhand_slot_window.texture = "ui1";
  rhand_slot_window.border = 1;
  rhand_slot_window.size = {x_size, y_size};
  rhand_slot_window.pos = {menu_base.pos.x() + x_offset, menu_base.pos.y() + y_offset};

  y_offset += y_spacing;

  UIElement lfoot_slot_label;
  lfoot_slot_label.text = "L Foot";
  lfoot_slot_label.text_texture = "inventory-lfoot-slot-label-texture";
  lfoot_slot_label.size = {60, 20};
  lfoot_slot_label.pos = {menu_base.pos.x() + x_offset - 60, menu_base.pos.y() + y_offset};

  sdl_interface.create_texture_from_text(
    lfoot_slot_label.text, lfoot_slot_label.text_texture, "jura-small");

  ScalableElement lfoot_slot_window;
  lfoot_slot_window.type = "window1";
  lfoot_slot_window.texture = "ui1";
  lfoot_slot_window.border = 1;
  lfoot_slot_window.size = {x_size, y_size};
  lfoot_slot_window.pos = {menu_base.pos.x() + x_offset, menu_base.pos.y() + y_offset};

  y_offset += y_spacing;

  UIElement rfoot_slot_label;
  rfoot_slot_label.text = "R Foot";
  rfoot_slot_label.text_texture = "inventory-rfoot-slot-label-texture";
  rfoot_slot_label.size = {60, 20};
  rfoot_slot_label.pos = {menu_base.pos.x() + x_offset - 60, menu_base.pos.y() + y_offset};

  sdl_interface.create_texture_from_text(
    rfoot_slot_label.text, rfoot_slot_label.text_texture, "jura-small");

  ScalableElement rfoot_slot_window;
  rfoot_slot_window.type = "window1";
  rfoot_slot_window.texture = "ui1";
  rfoot_slot_window.border = 1;
  rfoot_slot_window.size = {x_size, y_size};
  rfoot_slot_window.pos = {menu_base.pos.x() + x_offset, menu_base.pos.y() + y_offset};

  elements.push_back(head_slot_label);
  elements.push_back(torso_slot_label);
  elements.push_back(back_slot_label);
  elements.push_back(larm_slot_label);
  elements.push_back(rarm_slot_label);
  elements.push_back(lleg_slot_label);
  elements.push_back(rleg_slot_label);
  elements.push_back(lhand_slot_label);
  elements.push_back(rhand_slot_label);
  elements.push_back(lfoot_slot_label);
  elements.push_back(rfoot_slot_label);

  scalable_elements.push_back(head_slot_window);
  scalable_elements.push_back(torso_slot_window);
  scalable_elements.push_back(back_slot_window);
  scalable_elements.push_back(larm_slot_window);
  scalable_elements.push_back(rarm_slot_window);
  scalable_elements.push_back(lleg_slot_window);
  scalable_elements.push_back(rleg_slot_window);
  scalable_elements.push_back(lhand_slot_window);
  scalable_elements.push_back(rhand_slot_window);
  scalable_elements.push_back(lfoot_slot_window);
  scalable_elements.push_back(rfoot_slot_window);
}



void InventoryUISystem::update_preview_image()
{
  if (active_slot_index < current_slots.size())
  {
    auto& type(current_slots[active_slot_index].type);

    active_item_preview_image.clip_rect.x = Item_Data[type].clip_rect.x;
    active_item_preview_image.clip_rect.y = Item_Data[type].clip_rect.y;
  }
  else
  {
    active_item_preview_image.clip_rect.x = 19 * HALF_UNIT;
    active_item_preview_image.clip_rect.y = 9 * HALF_UNIT;
  }
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
