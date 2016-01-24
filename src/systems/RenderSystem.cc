#include "RenderSystem.h"

#include <iostream>
#include <SDL2/SDL_image.h>

using namespace ld;
using namespace std;

RenderSystem::RenderSystem(
  SDL_Window* window_, SDL_Renderer* renderer_, MapSystem& map_system_
)
  : window(window_),
    renderer(renderer_),
    screen(SDL_GetWindowSurface(window)),
    map_system(map_system_),
    textures()
{
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

  setup_textures();

  cout << "Render system ready" << endl;
}


void RenderSystem::setup_textures()
{
  textures["kadijah"] = load_texture("kadijah");

}


SDL_Texture* RenderSystem::load_texture(std::string name)
{
  string path = "media/textures/" + name + ".png";

  return IMG_LoadTexture(renderer, path.c_str());
}


void RenderSystem::update()
{
  SDL_RenderClear(renderer);

  SDL_RenderCopy(renderer, textures["kadijah"], nullptr, nullptr);
  SDL_RenderPresent(renderer);
}
