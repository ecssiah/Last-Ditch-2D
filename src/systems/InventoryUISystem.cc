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
    user(_entity_system.get_user()),
    active_category("All")
{
  setup_base();
  setup_sort_buttons();
  setup_inventory_list();
  setup_inventory_info();
  setup_equipment_slots();
}


void InventoryUISystem::update()
{
  if (active_user.inventory.modified)
  {
    // Do something here?
  }

  if (input.mouse_dragged) handle_dragged_event();
  if (input.mouse_wheel) handle_wheel_event();
  if (input.activate) handle_activation_event();
}


void InventoryUISystem::render()
{
  sdl_interface.render_window_element(base_window);
  sdl_interface.render_list_element(inventory_list);

  for (auto& element : sort_buttons) sdl_interface.render_button_element(element);
  for (auto& element : equipment_slot_windows) sdl_interface.render_window_element(element);
  for (auto& element : equipment_slot_labels) sdl_interface.render_text_element(element);

  sdl_interface.render_ui_element(preview_image);
}


void InventoryUISystem::setup()
{
}


void InventoryUISystem::setup_base()
{
  base_window.type = "window1";
  base_window.texture = "ui1";
  base_window.size = {BASE_WINDOW_SIZE_X, BASE_WINDOW_SIZE_Y};
  base_window.pos =
    {(SCREEN_SIZE_X - BASE_WINDOW_SIZE_X) / 2,
     (SCREEN_SIZE_Y - BASE_WINDOW_SIZE_Y) / 2};
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

  ButtonElement sort_all_button;
  sort_all_button.type = "button1";
  sort_all_button.texture = "ui1";
  sort_all_button.text = "All";
  sort_all_button.text_texture = "sort-all";
  sort_all_button.border = 4;
  sort_all_button.size = {all_button_width, button_height};
  sort_all_button.pos = {base_window.pos.x() + x_offset, base_window.pos.y() + y_offset};

  x_offset += sort_all_button.size.x() + x_spacing;

  ButtonElement sort_weapons_button;
  sort_weapons_button.type = "button1";
  sort_weapons_button.texture = "ui1";
  sort_weapons_button.text = "Weapons";
  sort_weapons_button.text_texture = "sort-weapons";
  sort_weapons_button.border = 4;
  sort_weapons_button.size = {weapons_button_width, button_height};
  sort_weapons_button.pos = {base_window.pos.x() + x_offset, base_window.pos.y() + y_offset};

  x_offset += sort_weapons_button.size.x() + x_spacing;

  ButtonElement sort_clothing_button;
  sort_clothing_button.type = "button1";
  sort_clothing_button.texture = "ui1";
  sort_clothing_button.text = "Clothing";
  sort_clothing_button.text_texture = "sort-clothing";
  sort_clothing_button.border = 4;
  sort_clothing_button.size = {clothing_button_width, button_height};
  sort_clothing_button.pos = {base_window.pos.x() + x_offset, base_window.pos.y() + y_offset};

  x_offset += sort_clothing_button.size.x() + x_spacing;

  ButtonElement sort_utility_button;
  sort_utility_button.type = "button1";
  sort_utility_button.texture = "ui1";
  sort_utility_button.text = "Utility";
  sort_utility_button.text_texture = "sort-utility";
  sort_utility_button.border = 4;
  sort_utility_button.size = {utility_button_width, button_height};
  sort_utility_button.pos = {base_window.pos.x() + x_offset, base_window.pos.y() + y_offset};

  x_offset += sort_utility_button.size.x() + x_spacing;

  ButtonElement sort_production_button;
  sort_production_button.type = "button1";
  sort_production_button.texture = "ui1";
  sort_production_button.text = "Production";
  sort_production_button.text_texture = "sort-production";
  sort_production_button.border = 4;
  sort_production_button.size = {production_button_width, button_height};
  sort_production_button.pos = {base_window.pos.x() + x_offset, base_window.pos.y() + y_offset};

  generate_button_element(sort_all_button);
  generate_button_element(sort_weapons_button);
  generate_button_element(sort_clothing_button);
  generate_button_element(sort_utility_button);
  generate_button_element(sort_production_button);

  sort_buttons.push_back(sort_all_button);
  sort_buttons.push_back(sort_weapons_button);
  sort_buttons.push_back(sort_clothing_button);
  sort_buttons.push_back(sort_utility_button);
  sort_buttons.push_back(sort_production_button);
}


void InventoryUISystem::setup_preview_image()
{
  auto x(base_window.pos.x() + 16);
  auto y(base_window.pos.y() + 40);

  WindowElement preview_window;
  preview_window.type = "window1";
  preview_window.texture = "ui1";
  preview_window.border = 1;
  preview_window.size = {HALF_UNIT + 10, HALF_UNIT + 10};
  preview_window.pos = {x, y};

  preview_image.type = "image1";
  preview_image.texture = "items1";
  preview_image.size = {HALF_UNIT, HALF_UNIT};
  preview_image.pos = {x + 5, y + 5};
}


void InventoryUISystem::setup_inventory_list()
{
  inventory_list.type = "list1";
  inventory_list.texture = "inventory-list";
  inventory_list.size = {360, 300};
  inventory_list.pos = {base_window.pos.x() + 16, base_window.pos.y() + 200};

  sdl_interface.generate_list_element(inventory_list);
}


void InventoryUISystem::setup_equipment_slots()
{
  auto x_offset(440);
  auto y_offset(40);
  auto x_size(210);
  auto y_size(18);
  auto y_spacing(20);

  WindowElement head_slot_window;
  head_slot_window.texture = "ui1";
  head_slot_window.border = 1;
  head_slot_window.size = {x_size, y_size};
  head_slot_window.pos = {base_window.pos.x() + x_offset, base_window.pos.y() + y_offset};

  TextElement head_slot_label;
  head_slot_label.text = "Head";
  head_slot_label.text_texture = "head-slot-label";
  head_slot_label.size = {60, 20};
  head_slot_label.pos = {base_window.pos.x() + x_offset - 60, base_window.pos.y() + y_offset};

  y_offset += y_spacing;

  WindowElement torso_slot_window;
  torso_slot_window.texture = "ui1";
  torso_slot_window.border = 1;
  torso_slot_window.size = {x_size, y_size};
  torso_slot_window.pos = {base_window.pos.x() + x_offset, base_window.pos.y() + y_offset};

  TextElement torso_slot_label;
  torso_slot_label.text = "Torso";
  torso_slot_label.text_texture = "torso-slot-label";
  torso_slot_label.size = {60, 20};
  torso_slot_label.pos = {base_window.pos.x() + x_offset - 60, base_window.pos.y() + y_offset};

  y_offset += y_spacing;

  WindowElement back_slot_window;
  back_slot_window.texture = "ui1";
  back_slot_window.border = 1;
  back_slot_window.size = {x_size, y_size};
  back_slot_window.pos = {base_window.pos.x() + x_offset, base_window.pos.y() + y_offset};

  TextElement back_slot_label;
  back_slot_label.text = "Back";
  back_slot_label.text_texture = "back-slot-label";
  back_slot_label.size = {60, 20};
  back_slot_label.pos = {base_window.pos.x() + x_offset - 60, base_window.pos.y() + y_offset};

  y_offset += y_spacing;

  WindowElement larm_slot_window;
  larm_slot_window.texture = "ui1";
  larm_slot_window.border = 1;
  larm_slot_window.size = {x_size, y_size};
  larm_slot_window.pos = {base_window.pos.x() + x_offset, base_window.pos.y() + y_offset};

  TextElement larm_slot_label;
  larm_slot_label.text = "L Arm";
  larm_slot_label.text_texture = "larm-slot-label";
  larm_slot_label.size = {60, 20};
  larm_slot_label.pos = {base_window.pos.x() + x_offset - 60, base_window.pos.y() + y_offset};

  y_offset += y_spacing;

  WindowElement rarm_slot_window;
  rarm_slot_window.texture = "ui1";
  rarm_slot_window.border = 1;
  rarm_slot_window.size = {x_size, y_size};
  rarm_slot_window.pos = {base_window.pos.x() + x_offset, base_window.pos.y() + y_offset};

  TextElement rarm_slot_label;
  rarm_slot_label.text = "R Arm";
  rarm_slot_label.text_texture = "rarm-slot-label";
  rarm_slot_label.size = {60, 20};
  rarm_slot_label.pos = {base_window.pos.x() + x_offset - 60, base_window.pos.y() + y_offset};

  y_offset += y_spacing;

  WindowElement lleg_slot_window;
  lleg_slot_window.texture = "ui1";
  lleg_slot_window.border = 1;
  lleg_slot_window.size = {x_size, y_size};
  lleg_slot_window.pos = {base_window.pos.x() + x_offset, base_window.pos.y() + y_offset};

  TextElement lleg_slot_label;
  lleg_slot_label.text = "L Leg";
  lleg_slot_label.text_texture = "lleg-slot-label";
  lleg_slot_label.size = {60, 20};
  lleg_slot_label.pos = {base_window.pos.x() + x_offset - 60, base_window.pos.y() + y_offset};

  y_offset += y_spacing;

  WindowElement rleg_slot_window;
  rleg_slot_window.texture = "ui1";
  rleg_slot_window.border = 1;
  rleg_slot_window.size = {x_size, y_size};
  rleg_slot_window.pos = {base_window.pos.x() + x_offset, base_window.pos.y() + y_offset};

  TextElement rleg_slot_label;
  rleg_slot_label.text = "R Leg";
  rleg_slot_label.text_texture = "rleg-slot-label";
  rleg_slot_label.size = {60, 20};
  rleg_slot_label.pos = {base_window.pos.x() + x_offset - 60, base_window.pos.y() + y_offset};

  y_offset += y_spacing;

  WindowElement lhand_slot_window;
  lhand_slot_window.texture = "ui1";
  lhand_slot_window.border = 1;
  lhand_slot_window.size = {x_size, y_size};
  lhand_slot_window.pos = {base_window.pos.x() + x_offset, base_window.pos.y() + y_offset};

  TextElement lhand_slot_label;
  lhand_slot_label.text = "L Hand";
  lhand_slot_label.text_texture = "lhand-slot-label";
  lhand_slot_label.size = {60, 20};
  lhand_slot_label.pos = {base_window.pos.x() + x_offset - 60, base_window.pos.y() + y_offset};

  y_offset += y_spacing;

  WindowElement rhand_slot_window;
  rhand_slot_window.texture = "ui1";
  rhand_slot_window.border = 1;
  rhand_slot_window.size = {x_size, y_size};
  rhand_slot_window.pos = {base_window.pos.x() + x_offset, base_window.pos.y() + y_offset};

  TextElement rhand_slot_label;
  rhand_slot_label.text = "R Hand";
  rhand_slot_label.text_texture = "rhand-slot-label";
  rhand_slot_label.size = {60, 20};
  rhand_slot_label.pos = {base_window.pos.x() + x_offset - 60, base_window.pos.y() + y_offset};

  y_offset += y_spacing;

  WindowElement lfoot_slot_window;
  lfoot_slot_window.texture = "ui1";
  lfoot_slot_window.border = 1;
  lfoot_slot_window.size = {x_size, y_size};
  lfoot_slot_window.pos = {base_window.pos.x() + x_offset, base_window.pos.y() + y_offset};

  TextElement lfoot_slot_label;
  lfoot_slot_label.text = "L Foot";
  lfoot_slot_label.text_texture = "lfoot-slot-label";
  lfoot_slot_label.size = {60, 20};
  lfoot_slot_label.pos = {base_window.pos.x() + x_offset - 60, base_window.pos.y() + y_offset};

  y_offset += y_spacing;

  WindowElement rfoot_slot_window;
  rfoot_slot_window.texture = "ui1";
  rfoot_slot_window.border = 1;
  rfoot_slot_window.size = {x_size, y_size};
  rfoot_slot_window.pos = {base_window.pos.x() + x_offset, base_window.pos.y() + y_offset};

  TextElement rfoot_slot_label;
  rfoot_slot_label.text = "R Foot";
  rfoot_slot_label.text_texture = "rfoot-slot-label";
  rfoot_slot_label.size = {60, 20};
  rfoot_slot_label.pos = {base_window.pos.x() + x_offset - 60, base_window.pos.y() + y_offset};

  sdl_interface.generate_text_element(head_slot_label);
  sdl_interface.generate_text_element(torso_slot_label);
  sdl_interface.generate_text_element(back_slot_label);
  sdl_interface.generate_text_element(larm_slot_label);
  sdl_interface.generate_text_element(rarm_slot_label);
  sdl_interface.generate_text_element(lleg_slot_label);
  sdl_interface.generate_text_element(rleg_slot_label);
  sdl_interface.generate_text_element(lhand_slot_label);
  sdl_interface.generate_text_element(rhand_slot_label);
  sdl_interface.generate_text_element(lfoot_slot_label);
  sdl_interface.generate_text_element(rfoot_slot_label);

  equipment_slot_windows.push_back(head_slot_window);
  equipment_slot_windows.push_back(torso_slot_window);
  equipment_slot_windows.push_back(back_slot_window);
  equipment_slot_windows.push_back(larm_slot_window);
  equipment_slot_windows.push_back(rarm_slot_window);
  equipment_slot_windows.push_back(lleg_slot_window);
  equipment_slot_windows.push_back(rleg_slot_window);
  equipment_slot_windows.push_back(lhand_slot_window);
  equipment_slot_windows.push_back(rhand_slot_window);
  equipment_slot_windows.push_back(lfoot_slot_window);
  equipment_slot_windows.push_back(rfoot_slot_window);

  equipment_slot_labels.push_back(head_slot_label);
  equipment_slot_labels.push_back(torso_slot_label);
  equipment_slot_labels.push_back(back_slot_label);
  equipment_slot_labels.push_back(larm_slot_label);
  equipment_slot_labels.push_back(rarm_slot_label);
  equipment_slot_labels.push_back(lleg_slot_label);
  equipment_slot_labels.push_back(rleg_slot_label);
  equipment_slot_labels.push_back(lhand_slot_label);
  equipment_slot_labels.push_back(rhand_slot_label);
  equipment_slot_labels.push_back(lfoot_slot_label);
  equipment_slot_labels.push_back(rfoot_slot_label);
}


void InventoryUISystem::handle_dragged_event()
{
  if (point_intersects_element(input.left_mouse_pressed_pos, inventory_list))
  {
    inventory_list.scrolled_offset +=
      INVENTORY_MOUSE_SCROLL_RATE * input.mouse_drag_vector.y();
    inventory_list.scrolled_offset = clamp(inventory_list.scrolled_offset, -100, 0);

    update_inventory_list();
  }
}


void InventoryUISystem::handle_wheel_event()
{
  inventory_list.scrolled_offset +=
    INVENTORY_WHEEL_SCROLL_RATE * input.mouse_wheel_vector.y();
  inventory_list.scrolled_offset = clamp(inventory_list.scrolled_offset, -100, 0);

  update_inventory_list();
}


void InventoryUISystem::handle_activation_event()
{
  for (auto& element : sort_buttons)
  {
    if (point_intersects_element(input.left_mouse_released_pos, element))
    {
      input.activate = false;

      active_category = element.text;
      update_inventory_list();

      return;
    }
  }

  if (point_intersects_element(input.left_mouse_released_pos, inventory_list))
  {
    input.activate = false;

    auto offset(
      input.left_mouse_released_pos.y() -
      inventory_list.pos.y() - inventory_list.scrolled_offset);

    inventory_list.selected_index = offset / MENU_BUTTON_SIZE_Y;

    update_inventory_list();

    return;
  }
}



void InventoryUISystem::update_preview_image()
{
  if (inventory_list.selected_index < inventory_list.text_elements.size())
  {
    auto& type(current_slots[inventory_list.selected_index].type);

    preview_image.clip_rect.x = Item_Data[type].clip_rect.x;
    preview_image.clip_rect.y = Item_Data[type].clip_rect.y;
  }
  else
  {
    preview_image.clip_rect.x = 19 * HALF_UNIT;
    preview_image.clip_rect.y = 9 * HALF_UNIT;
  }
}


void InventoryUISystem::update_inventory_list()
{
  set<Item> unique_items;
  unordered_map<string, unsigned> item_counts;

  for (auto& item : user.inventory.items)
  {
    ++item_counts[item.type];

    if (active_category == "All" || item.category == active_category)
      unique_items.insert(item);
  }

  current_slots.clear();
  inventory_list.entries.clear();
  vector<Item> items(unique_items.begin(), unique_items.end());

  for (auto i(0); i < items.size(); ++i)
  {
    auto& item(items[i]);
    auto& item_count(item_counts[item.type]);

    auto text(item.name);

    if (item_count != 1) text += " (" + to_string(item_count) + ")";

    inventory_list.entries.push_back(text);

    SlotInfo slot_info;
    slot_info.type = item.type;
    slot_info.count = item_count;

    current_slots.push_back(slot_info);
  }
}
