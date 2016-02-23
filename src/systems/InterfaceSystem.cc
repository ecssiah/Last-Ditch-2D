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
    date_and_time(),
    fonts(),
    textures()
{
  fonts["jura-medium"] = TTF_OpenFont("media/fonts/JuraMedium.ttf", 14);

  date_and_time.type = "date_and_time";
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
  stringstream ss;
  ss <<
    time_system.get_day() << "/" <<
    time_system.get_month() << "/" <<
    time_system.get_year() << " ";
  ss << time_system.get_hour() << ":";

  auto minute(time_system.get_minute());
  minute < 10 ? ss << "0" << minute : ss << minute;

  date_and_time.text = ss.str();

  auto surface =
    TTF_RenderText_Blended(fonts["jura-medium"], ss.str().c_str(), {236, 255, 255});

  textures[date_and_time.type] =
    SDL_CreateTextureFromSurface(sdl_interface.renderer, surface);
}


void InterfaceSystem::render()
{
  render_element_at(date_and_time, SCREEN_SIZE_X - 120, 6);
}


void InterfaceSystem::render_element_at(StaticElement& element, int x, int y)
{
  auto& texture(textures[element.type]);

  int w, h;
  SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

  SDL_Rect dest_rect;
  dest_rect.x = x;
  dest_rect.y = y;
  dest_rect.w = w;
  dest_rect.h = h;

  SDL_RenderCopy(sdl_interface.renderer, texture, nullptr, &dest_rect);
}
