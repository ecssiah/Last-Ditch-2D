#include "InventoryUISystem.h"

#include <algorithm>
#include <cassert>
#include <eigen3/Eigen/Geometry>
#include <functional>
#include <iostream>
#include <set>
#include <yaml-cpp/yaml.h>

#include "../../components/Item.h"
#include "../../constants/ItemConstants.h"
#include "../../constants/UIConstants.h"
#include "../../Utils.h"

using namespace Eigen;
using namespace std;
using namespace Utils;

namespace ld
{

InventoryUISystem::InventoryUISystem(
  Input& _input, SDL_Interface& _sdl_interface,
  EntitySystem& _entity_system, InventorySystem& _inventory_system
)
  : input(_input),
    sdl_interface(_sdl_interface),
    entity_system(_entity_system),
    inventory_system(_inventory_system),
    active_category("All")
{
  setup_base();
  setup_sort_buttons();
  setup_inventory_list();
  setup_preview_image();
  setup_equipment_slots();
}


void InventoryUISystem::update()
{
  if (input.mouse_dragged) handle_dragged_event();
  if (input.mouse_wheel) handle_wheel_event();
  if (input.activate) handle_activation_event();
}


void InventoryUISystem::render()
{
  sdl_interface.render_element(base_window);
  sdl_interface.render_element(inventory_list);

  for (auto& element : sort_buttons) sdl_interface.render_element(element);
  for (auto& element : equipment_slot_windows) sdl_interface.render_element(element);
  for (auto& element : equipment_slot_labels) sdl_interface.render_element(element);

  sdl_interface.render_element(preview_image);
}


void InventoryUISystem::setup_base()
{
  base_window.type = "window1";
  base_window.source_texture = "ui1";
  base_window.batch_texture = "ui1-batch";

  base_window.dest_rect.x = (SCREEN_SIZE_X - BASE_WINDOW_SIZE_X) / 2;
  base_window.dest_rect.y = (SCREEN_SIZE_Y - BASE_WINDOW_SIZE_Y) / 2;
  base_window.dest_rect.w = BASE_WINDOW_SIZE_X;
  base_window.dest_rect.h = BASE_WINDOW_SIZE_Y;
}


void InventoryUISystem::setup_sort_buttons()
{
  auto y_offset(180);
  auto x_offset(16);
  auto x_spacing(4);
  auto button_height(18);
  auto all_button_width(28);
  auto weapons_button_width(78);
  auto apparel_button_width(73);
  auto utility_button_width(52);
  auto resource_button_width(92);

  Button sort_all_button;
  sort_all_button.type = "button1";
  sort_all_button.source_texture = "ui1";
  sort_all_button.batch_texture = "ui1-batch";
  sort_all_button.text = "All";
  sort_all_button.border = 4;

  sort_all_button.dest_rect.x = base_window.dest_rect.x + x_offset;
  sort_all_button.dest_rect.y = base_window.dest_rect.y + y_offset;
  sort_all_button.dest_rect.w = all_button_width;
  sort_all_button.dest_rect.h = button_height;

  x_offset += sort_all_button.dest_rect.w + x_spacing;

  Button sort_weapons_button;
  sort_weapons_button.type = "button1";
  sort_weapons_button.source_texture = "ui1";
  sort_weapons_button.batch_texture = "ui1-batch";
  sort_weapons_button.text = "Weapons";
  sort_weapons_button.border = 4;

  sort_weapons_button.dest_rect.x = base_window.dest_rect.x + x_offset;
  sort_weapons_button.dest_rect.y = base_window.dest_rect.y + y_offset;
  sort_weapons_button.dest_rect.w = weapons_button_width;
  sort_weapons_button.dest_rect.h = button_height;

  x_offset += sort_weapons_button.dest_rect.w + x_spacing;

  Button sort_apparel_button;
  sort_apparel_button.type = "button1";
  sort_apparel_button.source_texture = "ui1";
  sort_apparel_button.batch_texture = "ui1-batch";
  sort_apparel_button.text = "Apparel";
  sort_apparel_button.border = 4;

  sort_apparel_button.dest_rect.x = base_window.dest_rect.x + x_offset;
  sort_apparel_button.dest_rect.y = base_window.dest_rect.y + y_offset;
  sort_apparel_button.dest_rect.w = apparel_button_width;
  sort_apparel_button.dest_rect.h = button_height;

  x_offset += sort_apparel_button.dest_rect.w + x_spacing;

  Button sort_utility_button;
  sort_utility_button.type = "button1";
  sort_utility_button.source_texture = "ui1";
  sort_utility_button.batch_texture = "ui1-batch";
  sort_utility_button.text = "Utility";
  sort_utility_button.border = 4;

  sort_utility_button.dest_rect.x = base_window.dest_rect.x + x_offset;
  sort_utility_button.dest_rect.y = base_window.dest_rect.y + y_offset;
  sort_utility_button.dest_rect.w = utility_button_width;
  sort_utility_button.dest_rect.h = button_height;

  x_offset += sort_utility_button.dest_rect.w + x_spacing;

  Button sort_resource_button;
  sort_resource_button.type = "button1";
  sort_resource_button.source_texture = "ui1";
  sort_resource_button.batch_texture = "ui1-batch";
  sort_resource_button.text = "Resource";
  sort_resource_button.border = 4;

  sort_resource_button.dest_rect.x = base_window.dest_rect.x + x_offset;
  sort_resource_button.dest_rect.y = base_window.dest_rect.y + y_offset;
  sort_resource_button.dest_rect.w = resource_button_width;
  sort_resource_button.dest_rect.h = button_height;

  sort_buttons.push_back(sort_all_button);
  sort_buttons.push_back(sort_weapons_button);
  sort_buttons.push_back(sort_apparel_button);
  sort_buttons.push_back(sort_utility_button);
  sort_buttons.push_back(sort_resource_button);
}


void InventoryUISystem::setup_preview_image()
{
  auto x(base_window.dest_rect.x + 16);
  auto y(base_window.dest_rect.y + 40);

  Window preview_window;
  preview_window.type = "window1";
  preview_window.source_texture = "ui1";
  preview_window.batch_texture = "ui1-batch";
  preview_window.border = 1;
  preview_window.size = {HALF_UNIT + 10, HALF_UNIT + 10};

  preview_window.dest_rect.x = x;
  preview_window.dest_rect.y = y;
  preview_window.dest_rect.w = HALF_UNIT + 10;
  preview_window.dest_rect.h = HALF_UNIT + 10;

  preview_image.type = "image1";
  preview_image.source_texture = "items1";
  preview_image.batch_texture = "ui1-batch";
  preview_image.size = {HALF_UNIT, HALF_UNIT};

  preview_image.dest_rect.x = x + 5;
  preview_image.dest_rect.y = y + 5;
  preview_image.dest_rect.w = HALF_UNIT;
  preview_image.dest_rect.h = HALF_UNIT;
}


void InventoryUISystem::setup_inventory_list()
{
  inventory_list.type = "list1";
  inventory_list.source_texture = "ui1";
  inventory_list.batch_texture = "ui1-batch";
  inventory_list.size = {360, 300};

  inventory_list.dest_rect.x = base_window.dest_rect.x + 16;
  inventory_list.dest_rect.y = base_window.dest_rect.y + 200;
  inventory_list.dest_rect.w = 360;
  inventory_list.dest_rect.h = 300;
}


void InventoryUISystem::setup_equipment_slots()
{
  auto x_offset(440);
  auto y_offset(40);
  auto x_size(210);
  auto y_size(18);
  auto y_spacing(20);
  auto label_offset(60);

  Window head_slot_window;
  head_slot_window.type = "window2";
  head_slot_window.source_texture = "ui1";
  head_slot_window.batch_texture = "ui1-batch";
  head_slot_window.border = 1;

  head_slot_window.dest_rect.x = base_window.dest_rect.x + x_offset;
  head_slot_window.dest_rect.y = base_window.dest_rect.y + y_offset;
  head_slot_window.dest_rect.w = x_size;
  head_slot_window.dest_rect.h = y_size;

  Text head_slot_label;
  head_slot_label.type = "label1";
  head_slot_label.source_texture = "ui1";
  head_slot_label.batch_texture = "ui1-batch";
  head_slot_label.text = "Head";

  head_slot_label.dest_rect.x = base_window.dest_rect.x + x_offset - label_offset;
  head_slot_label.dest_rect.y = base_window.dest_rect.y + y_offset;
  head_slot_label.dest_rect.w = x_size;
  head_slot_label.dest_rect.h = y_size;

  y_offset += y_spacing;

  Window torso_slot_window;
  torso_slot_window.type = "window2";
  torso_slot_window.source_texture = "ui1";
  torso_slot_window.batch_texture = "ui1-batch";
  torso_slot_window.border = 1;

  torso_slot_window.dest_rect.x = base_window.dest_rect.x + x_offset;
  torso_slot_window.dest_rect.y = base_window.dest_rect.y + y_offset;
  torso_slot_window.dest_rect.w = x_size;
  torso_slot_window.dest_rect.h = y_size;

  Text torso_slot_label;
  torso_slot_label.type = "label1";
  torso_slot_label.source_texture = "ui1";
  torso_slot_label.batch_texture = "ui1-batch";
  torso_slot_label.text = "Torso";

  torso_slot_label.dest_rect.x = base_window.dest_rect.x + x_offset - label_offset;
  torso_slot_label.dest_rect.y = base_window.dest_rect.y + y_offset;
  torso_slot_label.dest_rect.w = x_size;
  torso_slot_label.dest_rect.h = y_size;

  y_offset += y_spacing;

  Window back_slot_window;
  back_slot_window.type = "window2";
  back_slot_window.source_texture = "ui1";
  back_slot_window.batch_texture = "ui1-batch";
  back_slot_window.border = 1;

  back_slot_window.dest_rect.x = base_window.dest_rect.x + x_offset;
  back_slot_window.dest_rect.y = base_window.dest_rect.y + y_offset;
  back_slot_window.dest_rect.w = x_size;
  back_slot_window.dest_rect.h = y_size;

  Text back_slot_label;
  back_slot_label.type = "label1";
  back_slot_label.source_texture = "ui1";
  back_slot_label.batch_texture = "ui1-batch";
  back_slot_label.text = "Back";

  back_slot_label.dest_rect.x = base_window.dest_rect.x + x_offset - label_offset;
  back_slot_label.dest_rect.y = base_window.dest_rect.y + y_offset;
  back_slot_label.dest_rect.w = x_size;
  back_slot_label.dest_rect.h = y_size;

  y_offset += y_spacing;

  Window larm_slot_window;
  larm_slot_window.type = "window2";
  larm_slot_window.source_texture = "ui1";
  larm_slot_window.batch_texture = "ui1-batch";
  larm_slot_window.border = 1;

  larm_slot_window.dest_rect.x = base_window.dest_rect.x + x_offset;
  larm_slot_window.dest_rect.y = base_window.dest_rect.y + y_offset;
  larm_slot_window.dest_rect.w = x_size;
  larm_slot_window.dest_rect.h = y_size;

  Text larm_slot_label;
  larm_slot_label.type = "label1";
  larm_slot_label.source_texture = "ui1";
  larm_slot_label.batch_texture = "ui1-batch";
  larm_slot_label.text = "L Arm";

  larm_slot_label.dest_rect.x = base_window.dest_rect.x + x_offset - label_offset;
  larm_slot_label.dest_rect.y = base_window.dest_rect.y + y_offset;
  larm_slot_label.dest_rect.w = x_size;
  larm_slot_label.dest_rect.h = y_size;

  y_offset += y_spacing;

  Window rarm_slot_window;
  rarm_slot_window.type = "window2";
  rarm_slot_window.source_texture = "ui1";
  rarm_slot_window.batch_texture = "ui1-batch";
  rarm_slot_window.border = 1;

  rarm_slot_window.dest_rect.x = base_window.dest_rect.x + x_offset;
  rarm_slot_window.dest_rect.y = base_window.dest_rect.y + y_offset;
  rarm_slot_window.dest_rect.w = x_size;
  rarm_slot_window.dest_rect.h = y_size;

  Text rarm_slot_label;
  rarm_slot_label.type = "label1";
  rarm_slot_label.source_texture = "ui1";
  rarm_slot_label.batch_texture = "ui1-batch";
  rarm_slot_label.text = "R Arm";

  rarm_slot_label.dest_rect.x = base_window.dest_rect.x + x_offset - label_offset;
  rarm_slot_label.dest_rect.y = base_window.dest_rect.y + y_offset;
  rarm_slot_label.dest_rect.w = x_size;
  rarm_slot_label.dest_rect.h = y_size;

  y_offset += y_spacing;

  Window lhand_slot_window;
  lhand_slot_window.type = "window2";
  lhand_slot_window.source_texture = "ui1";
  lhand_slot_window.batch_texture = "ui1-batch";
  lhand_slot_window.border = 1;

  lhand_slot_window.dest_rect.x = base_window.dest_rect.x + x_offset;
  lhand_slot_window.dest_rect.y = base_window.dest_rect.y + y_offset;
  lhand_slot_window.dest_rect.w = x_size;
  lhand_slot_window.dest_rect.h = y_size;

  Text lhand_slot_label;
  lhand_slot_label.type = "label1";
  lhand_slot_label.source_texture = "ui1";
  lhand_slot_label.batch_texture = "ui1-batch";
  lhand_slot_label.text = "L Hand";

  lhand_slot_label.dest_rect.x = base_window.dest_rect.x + x_offset - label_offset;
  lhand_slot_label.dest_rect.y = base_window.dest_rect.y + y_offset;
  lhand_slot_label.dest_rect.w = x_size;
  lhand_slot_label.dest_rect.h = y_size;

  y_offset += y_spacing;

  Window rhand_slot_window;
  rhand_slot_window.type = "window2";
  rhand_slot_window.source_texture = "ui1";
  rhand_slot_window.batch_texture = "ui1-batch";
  rhand_slot_window.border = 1;

  rhand_slot_window.dest_rect.x = base_window.dest_rect.x + x_offset;
  rhand_slot_window.dest_rect.y = base_window.dest_rect.y + y_offset;
  rhand_slot_window.dest_rect.w = x_size;
  rhand_slot_window.dest_rect.h = y_size;

  Text rhand_slot_label;
  rhand_slot_label.type = "label1";
  rhand_slot_label.source_texture = "ui1";
  rhand_slot_label.batch_texture = "ui1-batch";
  rhand_slot_label.text = "R Hand";

  rhand_slot_label.dest_rect.x = base_window.dest_rect.x + x_offset - label_offset;
  rhand_slot_label.dest_rect.y = base_window.dest_rect.y + y_offset;
  rhand_slot_label.dest_rect.w = x_size;
  rhand_slot_label.dest_rect.h = y_size;

  y_offset += y_spacing;

  Window lleg_slot_window;
  lleg_slot_window.type = "window2";
  lleg_slot_window.source_texture = "ui1";
  lleg_slot_window.batch_texture = "ui1-batch";
  lleg_slot_window.border = 1;

  lleg_slot_window.dest_rect.x = base_window.dest_rect.x + x_offset;
  lleg_slot_window.dest_rect.y = base_window.dest_rect.y + y_offset;
  lleg_slot_window.dest_rect.w = x_size;
  lleg_slot_window.dest_rect.h = y_size;

  Text lleg_slot_label;
  lleg_slot_label.type = "label1";
  lleg_slot_label.source_texture = "ui1";
  lleg_slot_label.batch_texture = "ui1-batch";
  lleg_slot_label.text = "L Leg";

  lleg_slot_label.dest_rect.x = base_window.dest_rect.x + x_offset - label_offset;
  lleg_slot_label.dest_rect.y = base_window.dest_rect.y + y_offset;
  lleg_slot_label.dest_rect.w = x_size;
  lleg_slot_label.dest_rect.h = y_size;

  y_offset += y_spacing;

  Window rleg_slot_window;
  rleg_slot_window.type = "window2";
  rleg_slot_window.source_texture = "ui1";
  rleg_slot_window.batch_texture = "ui1-batch";
  rleg_slot_window.border = 1;

  rleg_slot_window.dest_rect.x = base_window.dest_rect.x + x_offset;
  rleg_slot_window.dest_rect.y = base_window.dest_rect.y + y_offset;
  rleg_slot_window.dest_rect.w = x_size;
  rleg_slot_window.dest_rect.h = y_size;

  Text rleg_slot_label;
  rleg_slot_label.type = "label1";
  rleg_slot_label.source_texture = "ui1";
  rleg_slot_label.batch_texture = "ui1-batch";
  rleg_slot_label.text = "R Leg";

  rleg_slot_label.dest_rect.x = base_window.dest_rect.x + x_offset - label_offset;
  rleg_slot_label.dest_rect.y = base_window.dest_rect.y + y_offset;
  rleg_slot_label.dest_rect.w = x_size;
  rleg_slot_label.dest_rect.h = y_size;

  y_offset += y_spacing;

  Window lfoot_slot_window;
  lfoot_slot_window.type = "window2";
  lfoot_slot_window.source_texture = "ui1";
  lfoot_slot_window.batch_texture = "ui1-batch";
  lfoot_slot_window.border = 1;

  lfoot_slot_window.dest_rect.x = base_window.dest_rect.x + x_offset;
  lfoot_slot_window.dest_rect.y = base_window.dest_rect.y + y_offset;
  lfoot_slot_window.dest_rect.w = x_size;
  lfoot_slot_window.dest_rect.h = y_size;

  Text lfoot_slot_label;
  lfoot_slot_label.type = "label1";
  lfoot_slot_label.source_texture = "ui1";
  lfoot_slot_label.batch_texture = "ui1-batch";
  lfoot_slot_label.text = "L Foot";

  lfoot_slot_label.dest_rect.x = base_window.dest_rect.x + x_offset - label_offset;
  lfoot_slot_label.dest_rect.y = base_window.dest_rect.y + y_offset;
  lfoot_slot_label.dest_rect.w = x_size;
  lfoot_slot_label.dest_rect.h = y_size;

  y_offset += y_spacing;

  Window rfoot_slot_window;
  rfoot_slot_window.type = "window2";
  rfoot_slot_window.source_texture = "ui1";
  rfoot_slot_window.batch_texture = "ui1-batch";
  rfoot_slot_window.border = 1;

  rfoot_slot_window.dest_rect.x = base_window.dest_rect.x + x_offset;
  rfoot_slot_window.dest_rect.y = base_window.dest_rect.y + y_offset;
  rfoot_slot_window.dest_rect.w = x_size;
  rfoot_slot_window.dest_rect.h = y_size;

  Text rfoot_slot_label;
  rfoot_slot_label.type = "label1";
  rfoot_slot_label.source_texture = "ui1";
  rfoot_slot_label.batch_texture = "ui1-batch";
  rfoot_slot_label.text = "R Foot";

  rfoot_slot_label.dest_rect.x = base_window.dest_rect.x + x_offset - label_offset;
  rfoot_slot_label.dest_rect.y = base_window.dest_rect.y + y_offset;
  rfoot_slot_label.dest_rect.w = x_size;
  rfoot_slot_label.dest_rect.h = y_size;

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
    inventory_list.offset += INVENTORY_MOUSE_SCROLL_RATE * input.mouse_drag_vector.y();
    inventory_list.offset = clamp(inventory_list.offset, -100, 0);

    update_inventory_list();
  }
}


void InventoryUISystem::handle_wheel_event()
{
  inventory_list.offset += INVENTORY_WHEEL_SCROLL_RATE * input.mouse_wheel_vector.y();
  inventory_list.offset = clamp(inventory_list.offset, -100, 0);

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
      inventory_list.dest_rect.y -
      inventory_list.offset);

    inventory_list.index = offset / MENU_BUTTON_SIZE_Y;

    update_inventory_list();

    return;
  }
}



void InventoryUISystem::update_preview_image()
{
  if (inventory_list.index < inventory_list.entries.size())
  {
    auto& slot_info(current_slots[inventory_list.index]);

    preview_image.clip_rect.x = Item_Data[slot_info.type].clip_rect.x;
    preview_image.clip_rect.y = Item_Data[slot_info.type].clip_rect.y;
  }
  else
  {
    preview_image.clip_rect.x = 19 * HALF_UNIT;
    preview_image.clip_rect.y = 9 * HALF_UNIT;
  }
}


void InventoryUISystem::update_inventory_list()
{
  auto& user(entity_system.get_user(0));

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
    slot_info.category = item.category;
    slot_info.count = item_count;

    current_slots.push_back(slot_info);
  }
}

}
