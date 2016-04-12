#include "UISystem.h"

#include <iomanip>
#include <sstream>

#include "../../constants/UIConstants.h"

using namespace Eigen;
using namespace std;

namespace ld
{

UISystem::UISystem(
  SDL_Interface& _sdl_interface,
  Input& _input,
  TimeSystem& _time_system,
  EntitySystem& _entity_system,
  InventorySystem& _inventory_system
)
  : sdl_interface(_sdl_interface),
    input(_input),
    time_system(_time_system),
    entity_system(_entity_system),
    inventory_system(_inventory_system),
    inventory_ui_system(_input, _sdl_interface, _entity_system, _inventory_system),
    production_ui_system(_input, _sdl_interface),
    management_ui_system(_input, _sdl_interface),
    status_ui_system(_input, _sdl_interface),
    base_active(true),
    main_active(false)
{
  setup_base();
  setup_main();

  printf("UISystem ready\n");
}


void UISystem::update()
{
  if (input.menu) handle_menu_event();
  if (input.activate) handle_activate_event();

  if (base_active) update_base();

  if (inventory_ui_system.is_active()) inventory_ui_system.update();
  else if (production_ui_system.is_active()) production_ui_system.update();
  else if (management_ui_system.is_active()) management_ui_system.update();
  else if (status_ui_system.is_active()) status_ui_system.update();

}


void UISystem::render()
{
  if (base_active) render_base();

  if (main_active) render_main();
  else if (inventory_ui_system.is_active()) inventory_ui_system.render();
  else if (production_ui_system.is_active()) production_ui_system.render();
  else if (management_ui_system.is_active()) management_ui_system.render();
  else if (status_ui_system.is_active()) status_ui_system.render();
}


void UISystem::render_base()
{
  sdl_interface.render_element(date_and_time);
}


void UISystem::render_main()
{
  for (auto& button : main_buttons) sdl_interface.render_element(button);
}


void UISystem::setup_base()
{
  date_and_time.name = "date-and-time";
  date_and_time.type = "label1";
  date_and_time.source_texture = "ui1";
  date_and_time.batch_texture = "ui1-batch";
  date_and_time.text = time_system.get_string();
  date_and_time.size = {130, 20};

  date_and_time.dest_rect.x = 2;
  date_and_time.dest_rect.y = 2;
  date_and_time.dest_rect.w = 130;
  date_and_time.dest_rect.h = 20;

  sdl_interface.generate_label(date_and_time);
}


void UISystem::setup_main()
{
  auto vert_offset(100);
  auto horz_offset(160);

  Button inventory_button;
  inventory_button.name = "main-inventory-button";
  inventory_button.type = "button1";
  inventory_button.source_texture = "ui1";
  inventory_button.batch_texture = "ui1-batch";
  inventory_button.text = "Inventory";

  inventory_button.dest_rect.x = SCREEN_SIZE_X / 2 - MENU_BUTTON_SIZE_X / 2;
  inventory_button.dest_rect.y = SCREEN_SIZE_Y / 2 - MENU_BUTTON_SIZE_Y / 2 - vert_offset;
  inventory_button.dest_rect.w = MENU_BUTTON_SIZE_X;
  inventory_button.dest_rect.h = MENU_BUTTON_SIZE_Y;

  sdl_interface.generate_button(inventory_button);

  Button production_button;
  production_button.name = "main-production-button";
  production_button.type = "button1";
  production_button.source_texture = "ui1";
  production_button.batch_texture = "ui1-batch";
  production_button.text = "Production";

  production_button.dest_rect.x = SCREEN_SIZE_X / 2 - MENU_BUTTON_SIZE_X / 2 + horz_offset;
  production_button.dest_rect.y = SCREEN_SIZE_Y / 2 - MENU_BUTTON_SIZE_Y / 2;
  production_button.dest_rect.w = MENU_BUTTON_SIZE_X;
  production_button.dest_rect.h = MENU_BUTTON_SIZE_Y;

  sdl_interface.generate_button(production_button);

  Button management_button;
  management_button.name = "main-management-button";
  management_button.type = "button1";
  management_button.source_texture = "ui1";
  management_button.batch_texture = "ui1-batch";
  management_button.text = "Management";

  management_button.dest_rect.x = SCREEN_SIZE_X / 2 - MENU_BUTTON_SIZE_X / 2;
  management_button.dest_rect.y = SCREEN_SIZE_Y / 2 - MENU_BUTTON_SIZE_Y / 2 + vert_offset;
  management_button.dest_rect.w = MENU_BUTTON_SIZE_X;
  management_button.dest_rect.h = MENU_BUTTON_SIZE_Y;

  sdl_interface.generate_button(management_button);

  Button status_button;
  status_button.name = "main-status-button";
  status_button.type = "button1";
  status_button.source_texture = "ui1";
  status_button.batch_texture = "ui1-batch";
  status_button.text = "Status";

  status_button.dest_rect.x = SCREEN_SIZE_X / 2 - MENU_BUTTON_SIZE_X / 2 - horz_offset;
  status_button.dest_rect.y = SCREEN_SIZE_Y / 2 - MENU_BUTTON_SIZE_Y / 2;
  status_button.dest_rect.w = MENU_BUTTON_SIZE_X;
  status_button.dest_rect.h = MENU_BUTTON_SIZE_Y;

  sdl_interface.generate_button(status_button);

  main_buttons.push_back(inventory_button);
  main_buttons.push_back(production_button);
  main_buttons.push_back(management_button);
  main_buttons.push_back(status_button);
}


void UISystem::update_base()
{
  date_and_time.text = time_system.get_string();

  sdl_interface.generate_label(date_and_time);
}


void UISystem::handle_activate_event()
{
  for (auto& button : main_buttons)
  {
    input.activate = false;

    if (button.text == "Inventory")
    {
      main_active = false;
      inventory_ui_system.set_active(true);
    }
    else if (button.text == "Production")
    {
      main_active = false;
      production_ui_system.set_active(true);
    }
    else if (button.text == "Management")
    {
      main_active = false;
      management_ui_system.set_active(true);
    }
    else if (button.text == "Status")
    {
      main_active = false;
      status_ui_system.set_active(true);
    }
  }
}


void UISystem::handle_menu_event()
{
  input.menu = false;

  if (inventory_ui_system.is_active())
    inventory_ui_system.set_active(false);
  else if (production_ui_system.is_active())
    production_ui_system.set_active(false);
  else if (management_ui_system.is_active())
    management_ui_system.set_active(false);
  else if (status_ui_system.is_active())
    status_ui_system.set_active(false);
  else
    main_active = !main_active;
}

}
