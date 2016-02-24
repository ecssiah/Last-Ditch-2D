#include "InterfaceSystem.h"

#include <iomanip>
#include <sstream>

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
    base_resizable_elements(),
    date_and_time(nullptr)
{
  fonts["jura-medium"] = TTF_OpenFont("media/fonts/JuraMedium.ttf", 14);

  UIElement element;
  element.text = time_system.get_string();
  element.texture = "date_and_time";
  element.pos = {2, 2};
  base_ui_elements.push_back(element);
  date_and_time = &base_ui_elements.back();
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

  if (main_menu_active)
  {

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
