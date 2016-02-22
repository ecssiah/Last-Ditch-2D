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
    textures()
{
  fonts["jura-medium"] = TTF_OpenFont("media/fonts/JuraMedium.ttf", 14);
}


void InterfaceSystem::update()
{
  update_date_and_time();
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

  auto surface =
    TTF_RenderText_Blended(fonts["jura-medium"], ss.str().c_str(), {236, 255, 255});

  textures["time"] = SDL_CreateTextureFromSurface(sdl_interface.renderer, surface);
}


void InterfaceSystem::render()
{
  update_date_and_time();

  render_texture_at("debug", 10, SCREEN_SIZE_Y - 20);
  render_texture_at("time", SCREEN_SIZE_X - 120, 6);
}


void InterfaceSystem::render_texture_at(string texture_name, int x, int y)
{
  auto& texture(textures[texture_name]);

  int w, h;
  SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

  SDL_Rect dest_rect;
  dest_rect.x = x;
  dest_rect.y = y;
  dest_rect.w = w;
  dest_rect.h = h;

  SDL_RenderCopy(sdl_interface.renderer, texture, nullptr, &dest_rect);
}
