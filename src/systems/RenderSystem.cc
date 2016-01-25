#include "RenderSystem.h"

#include <iostream>
#include <SDL2/SDL_image.h>

#include "../constants/MapConstants.h"

using namespace ld;
using namespace std;

RenderSystem::RenderSystem(
  SDL_Window* window_, SDL_Renderer* renderer_,
  EntitySystem& entity_system_,
  MapSystem& map_system_,
  CameraSystem& camera_system_
)
  : window(window_),
    renderer(renderer_),
    entity_system(entity_system_),
    map_system(map_system_),
    camera_system(camera_system_),
    textures(),
    current_floor(0)
{
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

  setup_textures();

  cout << "Render system ready" << endl;
}


void RenderSystem::setup_textures()
{
  textures["kadijah"] = load_texture("kadijah");
  textures["chunk_floor1"] = load_texture("chunk_floor1");
  textures["tileset1"] = load_texture("tileset1");
}


SDL_Texture* RenderSystem::load_texture(std::string name)
{
  auto path = "media/textures/" + name + ".png";

  return IMG_LoadTexture(renderer, path.c_str());
}


void RenderSystem::update()
{
  SDL_RenderClear(renderer);

  for (auto x = 0; x < NUM_CHUNKS_X; ++x)
  {
    for (auto y = 0; y < NUM_CHUNKS_Y; ++y)
    {
      auto& chunk = map_system.get_chunk(x, y, current_floor);

      SDL_Rect dest_rect;
      dest_rect.x = TILE_SIZE * (chunk.pos.x() + camera_system.get_pos().x());
      dest_rect.y = TILE_SIZE * (chunk.pos.y() + camera_system.get_pos().y());
      dest_rect.w = TILES_PER_CHUNK_X;
      dest_rect.h = TILES_PER_CHUNK_Y;

      SDL_RenderCopy(renderer, textures[chunk.type], nullptr, &dest_rect);
    }
  }

  for (auto& entity : entity_system.get_dynamic_entities())
  {
    SDL_Rect dest_rect;
    dest_rect.x = TILE_SIZE * (entity.pos.x() + camera_system.get_pos().x());
    dest_rect.y = TILE_SIZE * (entity.pos.y() + camera_system.get_pos().y());
    dest_rect.w = TILE_SIZE;
    dest_rect.h = TILE_SIZE;

    SDL_RenderCopy(renderer, textures[entity.type], &entity.clip_rect, &dest_rect);
  }

  SDL_RenderPresent(renderer);
}


void RenderSystem::shutdown()
{
  for (auto& pair : textures)
    SDL_DestroyTexture(pair.second);
}
