#include "UISystem.h"

#include <iomanip>
#include <sstream>

#include "../constants/UIConstants.h"

using namespace ld;
using namespace Eigen;
using namespace std;

UISystem::UISystem(
  SDL_Interface& _sdl_interface,
  Input& _input,
  TimeSystem& _time_system,
  EntitySystem& _entity_system
)
  : sdl_interface(_sdl_interface),
    input(_input),
    time_system(_time_system),
    entity_system(_entity_system),
    inventory_ui_system(_sdl_interface, _input),
    production_ui_system(_sdl_interface, _input),
    management_ui_system(_sdl_interface, _input),
    status_ui_system(_sdl_interface, _input),
    base_active(true),
    main_active(false),
    active_user(_entity_system.get_active_user()),
    date_and_time(),
    base_ui_elements(),
    base_scalable_elements(),
    main_ui_elements(),
    main_scalable_elements()
{
  setup_base();
  setup_main();
}


void UISystem::setup_base()
{
  date_and_time.pos = {2, 2};
  date_and_time.size = {130, 20};
  date_and_time.text = time_system.get_string();
  date_and_time.text_texture = "date_and_time_text";
}


void UISystem::setup_main()
{
  auto vert_offset(100);
  auto horz_offset(160);

  ScalableElement inventory_button;
  inventory_button.type = "backdrop1";
  inventory_button.pos =
    {SCREEN_SIZE_X / 2 - MAIN_MENU_BUTTON_SIZE_X / 2,
     SCREEN_SIZE_Y / 2 - MAIN_MENU_BUTTON_SIZE_Y / 2 - vert_offset};
  inventory_button.size = {MAIN_MENU_BUTTON_SIZE_X, MAIN_MENU_BUTTON_SIZE_Y};
  inventory_button.texture = "ui1";
  inventory_button.text = "Inventory";
  inventory_button.text_texture = "inventory_button_text";

  sdl_interface.create_texture_from_text(
    inventory_button.text, inventory_button.text_texture);

  main_scalable_elements.push_back(inventory_button);

  ScalableElement production_button;
  production_button.type = "backdrop1";
  production_button.texture = "ui1";
  production_button.pos =
    {SCREEN_SIZE_X / 2 - MAIN_MENU_BUTTON_SIZE_X / 2 + horz_offset,
     SCREEN_SIZE_Y / 2 - MAIN_MENU_BUTTON_SIZE_Y / 2};
  production_button.size = {MAIN_MENU_BUTTON_SIZE_X, MAIN_MENU_BUTTON_SIZE_Y};
  production_button.text = "Production";
  production_button.text_texture = "production_button_text";

  sdl_interface.create_texture_from_text(
    production_button.text, production_button.text_texture);

  main_scalable_elements.push_back(production_button);

  ScalableElement management_button;
  management_button.type = "backdrop1";
  management_button.texture = "ui1";
  management_button.pos =
    {SCREEN_SIZE_X / 2 - MAIN_MENU_BUTTON_SIZE_X / 2,
     SCREEN_SIZE_Y / 2 - MAIN_MENU_BUTTON_SIZE_Y / 2 + vert_offset};
  management_button.size = {MAIN_MENU_BUTTON_SIZE_X, MAIN_MENU_BUTTON_SIZE_Y};
  management_button.text = "Management";
  management_button.text_texture = "management_button_text";

  sdl_interface.create_texture_from_text(
    management_button.text, management_button.text_texture);

  main_scalable_elements.push_back(management_button);

  ScalableElement status_button;
  status_button.type = "backdrop1";
  status_button.texture = "ui1";
  status_button.pos =
    {SCREEN_SIZE_X / 2 - MAIN_MENU_BUTTON_SIZE_X / 2 - horz_offset,
     SCREEN_SIZE_Y / 2 - MAIN_MENU_BUTTON_SIZE_Y / 2};
  status_button.size = {MAIN_MENU_BUTTON_SIZE_X, MAIN_MENU_BUTTON_SIZE_Y};
  status_button.text = "Status";
  status_button.text_texture = "status_button_text";

  sdl_interface.create_texture_from_text(
    status_button.text, status_button.text_texture);

  main_scalable_elements.push_back(status_button);

}


void UISystem::update()
{
  update_date_and_time();

  if (input.menu)
  {
    handle_menu_activation();
  }

  if (main_active)
    update_main_menu();
  else if (inventory_ui_system.is_active())
    inventory_ui_system.update();
  else if (production_ui_system.is_active())
    production_ui_system.update();
  else if (management_ui_system.is_active())
    management_ui_system.update();
  else if (status_ui_system.is_active())
    status_ui_system.update();

  if (input.activate)
  {
    cout << "Activation not used" << endl;
    input.activate = false;
  }
}


void UISystem::update_main_menu()
{
  if (input.activate)
  {
    auto element(find_scalable_element_at(input.mouse_pos));

    if (element)
    {
      input.activate = false;

      if (element->text == "Inventory")
      {
	main_active = false;
	inventory_ui_system.set_active(true);
      }
      else if (element->text == "Production")
      {
	main_active = false;
	production_ui_system.set_active(true);
      }
      else if (element->text == "Management")
      {
	main_active = false;
	management_ui_system.set_active(true);
      }
      else if (element->text == "Status")
      {
	main_active = false;
	status_ui_system.set_active(true);
      }
    }
  }
}


void UISystem::handle_menu_activation()
{
  input.menu = false;

  if (main_active)
  {
    input.pause = false;
    main_active = false;
  }
  else if (inventory_ui_system.is_active())
  {
    input.pause = false;
    inventory_ui_system.set_active(false);
  }
  else if (production_ui_system.is_active())
  {
    input.pause = false;
    production_ui_system.set_active(false);
  }
  else if (management_ui_system.is_active())
  {
    input.pause = false;
    management_ui_system.set_active(false);
  }
  else if (status_ui_system.is_active())
  {
    input.pause = false;
    status_ui_system.set_active(false);
  }
  else
  {
    input.pause = true;
    main_active = true;
  }
}


ScalableElement* UISystem::find_scalable_element_at(Vector2i& mouse_pos)
{
  for (auto& element : main_scalable_elements)
  {
    auto hit(
      mouse_pos.x() > element.pos.x() &&
      mouse_pos.x() < element.pos.x() + element.size.x() &&
      mouse_pos.y() > element.pos.y() &&
      mouse_pos.y() < element.pos.y() + element.size.y());

    if (hit)
      return &element;
  }

  return nullptr;
}


void UISystem::update_date_and_time()
{
  date_and_time.text = time_system.get_string();

  sdl_interface.create_texture_from_text(date_and_time.text, date_and_time.text_texture);
}


void UISystem::render()
{
  if (base_active)
  {
    sdl_interface.render_element(date_and_time);

    for (auto& element : base_ui_elements)
      sdl_interface.render_element(element);

    for (auto& element : base_scalable_elements)
      sdl_interface.render_scalable_element(element);
  }

  if (main_active)
  {
    for (auto& element : main_ui_elements)
      sdl_interface.render_element(element);

    for (auto& element : main_scalable_elements)
      sdl_interface.render_scalable_element(element);
  }

  if (inventory_ui_system.is_active()) inventory_ui_system.render();
  if (production_ui_system.is_active()) production_ui_system.render();
  if (management_ui_system.is_active()) management_ui_system.render();
  if (status_ui_system.is_active()) status_ui_system.render();
}
