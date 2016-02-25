#include "InterfaceSystem.h"

#include <iomanip>
#include <sstream>

#include "../constants/InterfaceConstants.h"

using namespace ld;
using namespace std;

InterfaceSystem::InterfaceSystem(
  SDL_Interface& _sdl_interface,
  Input& _input,
  TimeSystem& _time_system,
  EntitySystem& _entity_system
)
  : sdl_interface(_sdl_interface),
    input(_input),
    time_system(_time_system),
    entity_system(_entity_system),
    main_menu_active(),
    inventory_menu_active(),
    equipment_menu_active(),
    production_menu_active(),
    status_menu_active(),
    active_user(_entity_system.get_active_user()),
    fonts(),
    textures(),
    base_ui_elements(),
    base_scalable_elements(),
    date_and_time(nullptr),
    main_ui_elements(),
    main_scalable_elements()
{
  fonts["jura-medium"] = TTF_OpenFont("media/fonts/JuraMedium.ttf", 14);

  setup_base();
  setup_main();
  setup_inventory();
  setup_equipment();
  setup_production();
  setup_management();
}


void InterfaceSystem::setup_base()
{
  UIElement _date_and_time;
  _date_and_time.texture = "date_and_time";
  _date_and_time.pos = {2, 2};
  _date_and_time.text = time_system.get_string();

  base_ui_elements.push_back(_date_and_time);
  date_and_time = &base_ui_elements.back();
}


void InterfaceSystem::setup_main()
{
  ScalableElement inventory_button;
  inventory_button.texture = "backdrop1";
  inventory_button.pos =
    {SCREEN_SIZE_X / 2 - MAIN_MENU_BUTTON_SIZE_X / 2,
     SCREEN_SIZE_Y / 2 - MAIN_MENU_BUTTON_SIZE_Y / 2};
  inventory_button.text = "inventory";

  main_scalable_elements.push_back(inventory_button);
}


void InterfaceSystem::setup_inventory()
{

}


void InterfaceSystem::setup_equipment()
{

}


void InterfaceSystem::setup_production()
{

}


void InterfaceSystem::setup_management()
{

}


InterfaceSystem::~InterfaceSystem()
{
  for (auto& keyvalue : textures)
    SDL_DestroyTexture(keyvalue.second);
}


void InterfaceSystem::update()
{
  update_date_and_time();

  if (input.menu)
  {
    input.menu = false;
    main_menu_active = !main_menu_active;
  }
}


void InterfaceSystem::update_date_and_time()
{
  date_and_time->text = time_system.get_string();

  auto surface =
    TTF_RenderText_Blended(
      fonts["jura-medium"], date_and_time->text.c_str(), {236, 255, 255});

  if (textures[date_and_time->texture] != nullptr)
    SDL_DestroyTexture(textures[date_and_time->texture]);

  textures[date_and_time->texture] =
    SDL_CreateTextureFromSurface(sdl_interface.renderer, surface);
}


void InterfaceSystem::render()
{
  for (auto& element : base_ui_elements)
    render_element(element);

  for (auto& element : base_scalable_elements)
    render_scalable_element(element);

  if (main_menu_active)
  {
    for (auto& element : main_ui_elements)
      render_element(element);

    for (auto& element : main_scalable_elements)
      render_scalable_element(element);
  }
}


void InterfaceSystem::render_element(UIElement& element)
{
  auto& texture(textures[element.texture]);

  int w, h;
  SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

  SDL_Rect dest_rect;
  dest_rect.x = element.pos.x();
  dest_rect.y = element.pos.y();
  dest_rect.w = w;
  dest_rect.h = h;

  SDL_RenderCopy(sdl_interface.renderer, texture, nullptr, &dest_rect);
}


void InterfaceSystem::render_scalable_element(ScalableElement& element)
{
}
