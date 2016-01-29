#include "InterfaceSystem.h"

#include <iomanip>
#include <sstream>

using namespace ld;
using namespace std;

InterfaceSystem::InterfaceSystem(
  SDL_Interface& sdl_interface_,
  TimeSystem& time_system_,
  EntitySystem& entity_system_
)
  : sdl_interface(sdl_interface_),
    time_system(time_system_),
    entity_system(entity_system_),
    fonts(),
    textures()
{
  fonts["jura-medium"] = TTF_OpenFont("media/fonts/JuraMedium.ttf", 14);
}


void InterfaceSystem::update()
{
  auto active_user = entity_system.get_active_user();

  stringstream ss;
  ss << active_user->pos.x() << " " << active_user->pos.y();

  SDL_Surface* surface;

  surface = TTF_RenderText_Blended(
    fonts["jura-medium"], ss.str().c_str(), {230, 255, 255});

  textures["debug text"] = SDL_CreateTextureFromSurface(sdl_interface.renderer, surface);

  ss.str(string());
  ss << time_system.get_hour() << ":" << time_system.get_minute();

  surface = TTF_RenderText_Blended(fonts["jura-medium"], ss.str().c_str(), {230, 255, 255});

  textures["time"] = SDL_CreateTextureFromSurface(sdl_interface.renderer, surface);
}


void InterfaceSystem::render()
{
  auto& debug_texture = textures["debug text"];

  int w, h;
  SDL_QueryTexture(debug_texture, nullptr, nullptr, &w, &h);

  SDL_Rect dest_rect;
  dest_rect.x = 10;
  dest_rect.y = SCREEN_SIZE_Y - h;
  dest_rect.w = w;
  dest_rect.h = h;

  SDL_RenderCopy(sdl_interface.renderer, debug_texture, nullptr, &dest_rect);

  auto& time_texture = textures["time"];

  int tw, th;
  SDL_QueryTexture(time_texture, nullptr, nullptr, &tw, &th);

  SDL_Rect t_dest_rect;
  t_dest_rect.x = SCREEN_SIZE_X - tw - 10;
  t_dest_rect.y = 6;
  t_dest_rect.w = tw;
  t_dest_rect.h = th;

  SDL_RenderCopy(sdl_interface.renderer, time_texture, nullptr, &t_dest_rect);
}
