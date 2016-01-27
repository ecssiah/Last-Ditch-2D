#include "InterfaceSystem.h"

using namespace ld;
using namespace std;

InterfaceSystem::InterfaceSystem(SDL_Interface& sdl_interface_)
  : sdl_interface(sdl_interface_),
    test(nullptr),
    fonts()
{
  TTF_Font* font;
  font = TTF_OpenFont("media/fonts/JuraMedium.ttf", 22);

  test = TTF_RenderText_Blended(font, "This is really happening.", {220, 255, 255});

  test_tex = SDL_CreateTextureFromSurface(sdl_interface.renderer, test);
}


void InterfaceSystem::update()
{

}


void InterfaceSystem::render()
{
  SDL_RenderCopy(sdl_interface.renderer, test_tex, nullptr, nullptr);
}
