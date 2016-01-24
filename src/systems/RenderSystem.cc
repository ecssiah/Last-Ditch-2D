#include "RenderSystem.h"

#include <iostream>
#include <SDL2/SDL_image.h>

using namespace ld;
using namespace std;

RenderSystem::RenderSystem(
  SDL_Window* window_, SDL_Renderer* renderer_,
  EntitySystem& entity_system_,
  MapSystem& map_system_
)
  : window(window_),
    renderer(renderer_),
    entity_system(entity_system_),
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
  auto path = "media/textures/" + name + ".png";

  return IMG_LoadTexture(renderer, path.c_str());
}


void RenderSystem::update()
{
  SDL_RenderClear(renderer);

  for (auto& entity : entity_system.get_dynamic_entities())
  {
    SDL_Rect dest;
    dest.x = entity.pos.x();
    dest.y = entity.pos.y();
    dest.w = entity.clip_rect.w;
    dest.h = entity.clip_rect.h;

    SDL_RenderCopy(renderer, textures[entity.type], &entity.clip_rect, &dest);
  }

  SDL_RenderPresent(renderer);
}
