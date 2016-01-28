#include "InterfaceSystem.h"

#include <iomanip>
#include <sstream>

using namespace ld;
using namespace std;

InterfaceSystem::InterfaceSystem(SDL_Interface& sdl_interface_, EntitySystem& entity_system_)
  : sdl_interface(sdl_interface_),
    entity_system(entity_system_),
    debug_text("testing"),
    debug_text_texture(nullptr),
    fonts()
{
  fonts["jura-medium"] = TTF_OpenFont("media/fonts/JuraMedium.ttf", 14);
}


void InterfaceSystem::update()
{
  auto active_user = entity_system.get_active_user();

  stringstream ss;
  ss << active_user->pos.x() << " " << active_user->pos.y();
  debug_text = ss.str();

  auto surface = TTF_RenderText_Blended(
    fonts["jura-medium"], debug_text.c_str(), {220, 255, 255});

  debug_text_texture = SDL_CreateTextureFromSurface(sdl_interface.renderer, surface);
}


void InterfaceSystem::render()
{
  int w, h;
  SDL_QueryTexture(debug_text_texture, nullptr, nullptr, &w, &h);

  SDL_Rect dest_rect;
  dest_rect.x = 10;
  dest_rect.y = SCREEN_SIZE_Y - h;
  dest_rect.w = w;
  dest_rect.h = h;

  SDL_RenderCopy(sdl_interface.renderer, debug_text_texture, nullptr, &dest_rect);
}
