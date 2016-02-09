#include "RenderSystem.h"
#include <iostream>
#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL_image.h>

#include "../constants/MapConstants.h"
#include "../constants/RenderConstants.h"

using namespace ld;
using namespace Eigen;
using namespace std;

RenderSystem::RenderSystem(
  SDL_Interface& sdl_interface_,
  MapSystem& map_system_,
  EntitySystem& entity_system_,
  CameraSystem& camera_system_,
  InterfaceSystem& interface_system_,
  PhysicsSystem& physics_system_
)
  : sdl_interface(sdl_interface_),
    map_system(map_system_),
    entity_system(entity_system_),
    camera_system(camera_system_),
    interface_system(interface_system_),
    physics_system(physics_system_),
    debug_draw(sdl_interface.renderer, camera_system_),
    textures(),
    texture_coords(),
    type_to_texture_map(),
    current_floor(0)
{
  setup_textures();

  debug_draw.SetFlags(b2Draw::e_shapeBit);

  physics_system.set_debug_draw(debug_draw);

  cout << "Render system ready" << endl;
}


void RenderSystem::setup_textures()
{
  type_to_texture_map["chunk"] = "chunk_floor1";
  type_to_texture_map["kadijah"] = "kadijah";
  type_to_texture_map["scrub1"] = "items1";
  type_to_texture_map["container1"] = "items1";
  type_to_texture_map["wall"] = "tileset1";
  type_to_texture_map["door"] = "tileset1";
  type_to_texture_map["floor"] = "tileset1";
  type_to_texture_map["stairs_up"] = "tileset1";
  type_to_texture_map["stairs_down"] = "tileset1";

  textures["kadijah"] = load_texture("kadijah");
  textures["chunk_floor1"] = load_texture("chunk_floor1");

  textures["tileset1"] = load_texture("tileset1");
  texture_coords["wall1"] = {0, 0};
  texture_coords["door1"] = {0, 1};
  texture_coords["stairs_down1"] = {0, 2};
  texture_coords["stairs_up1"] = {1, 2};
  texture_coords["floor1"] = {0, 3};

  textures["items1"] = load_texture("items1");
  texture_coords["scrub1"] = {0, 0};
  texture_coords["container1"] = {1, 0};
}


SDL_Texture* RenderSystem::load_texture(std::string name)
{
  auto path("media/textures/" + name + ".png");

  return IMG_LoadTexture(sdl_interface.renderer, path.c_str());
}


void RenderSystem::render_chunk_floors()
{
  for (int x = 0; x < MAP_SIZE_X; x += TILES_PER_CHUNK_X)
  {
    for (int y = 0; y < MAP_SIZE_Y; y += TILES_PER_CHUNK_Y)
    {
      auto& chunk(map_system.get_chunk(x, y, current_floor));

      SDL_Rect dest_rect;
      dest_rect.x =
	PIXELS_PER_UNIT * (chunk.pos.x() - camera_system.get_pos().x()) + SCREEN_SIZE_X / 2;
      dest_rect.y =
	PIXELS_PER_UNIT * (chunk.pos.y() - camera_system.get_pos().y()) + SCREEN_SIZE_Y / 2;
      dest_rect.w = PIXELS_PER_UNIT * TILES_PER_CHUNK_X;
      dest_rect.h = PIXELS_PER_UNIT * TILES_PER_CHUNK_Y;

      SDL_RenderCopy(
	sdl_interface.renderer,
	textures[type_to_texture_map[chunk.type]],
	nullptr, &dest_rect);
    }
  }
}


void RenderSystem::render_entities(Chunk& chunk)
{
  for (auto x = 0; x < TILES_PER_CHUNK_X; ++x)
  {
    for (auto y = 0; y < TILES_PER_CHUNK_Y; ++y)
    {
      auto& entity(chunk.entities[x][y]);

      if (entity.type == "") continue;

      auto& texture_name(type_to_texture_map[entity.type]);

      cout << entity.type << endl;
      cout << texture_coords[entity.type].x() << " " << texture_coords[entity.type].y() << endl;

      SDL_Rect clip_rect;
      clip_rect.x = PIXELS_PER_UNIT * (texture_coords[entity.type].x());
      clip_rect.y = PIXELS_PER_UNIT * (texture_coords[entity.type].y());
      clip_rect.w = PIXELS_PER_UNIT;
      clip_rect.h = PIXELS_PER_UNIT;

      SDL_Rect dest_rect;
      dest_rect.x =
	PIXELS_PER_UNIT *
	(chunk.pos.x() + x - camera_system.get_pos().x()) + SCREEN_SIZE_X / 2;
      dest_rect.y =
	PIXELS_PER_UNIT *
	(chunk.pos.y() + y - camera_system.get_pos().y()) + SCREEN_SIZE_Y / 2;
      dest_rect.w = PIXELS_PER_UNIT;
      dest_rect.h = PIXELS_PER_UNIT;

      SDL_RenderCopyEx(
	sdl_interface.renderer,
	textures[texture_name],
	&clip_rect, &dest_rect,
	entity.rotation,
	nullptr,
	SDL_FLIP_NONE);
    }
  }
}


void RenderSystem::render_floor_entities(Chunk& chunk)
{
  for (auto x = 0; x < TILES_PER_CHUNK_X; ++x)
  {
    for (auto y = 0; y < TILES_PER_CHUNK_Y; ++y)
    {
      auto& entity(chunk.floor_entities[x][y]);

      if (entity.type == "") continue;

      auto& texture_name(type_to_texture_map[entity.type]);


      SDL_Rect clip_rect;
      clip_rect.x = PIXELS_PER_UNIT * (texture_coords[entity.type].x());
      clip_rect.y = PIXELS_PER_UNIT * (texture_coords[entity.type].y());
      clip_rect.w = PIXELS_PER_UNIT;
      clip_rect.h = PIXELS_PER_UNIT;

      SDL_Rect dest_rect;
      dest_rect.x =
	PIXELS_PER_UNIT *
	(chunk.pos.x() + x - camera_system.get_pos().x()) + SCREEN_SIZE_X / 2;
      dest_rect.y =
	PIXELS_PER_UNIT *
	(chunk.pos.y() + y - camera_system.get_pos().y()) + SCREEN_SIZE_Y / 2;
      dest_rect.w = PIXELS_PER_UNIT;
      dest_rect.h = PIXELS_PER_UNIT;

      SDL_RenderCopyEx(
	sdl_interface.renderer,
	textures[texture_name],
	&clip_rect, &dest_rect,
	entity.rotation,
	nullptr,
	SDL_FLIP_NONE);
    }
  }
}


void RenderSystem::render_items(Chunk& chunk)
{
  for (auto& item : chunk.items)
  {
    auto& texture_name(type_to_texture_map[item.type]);

    SDL_Rect clip_rect;
    clip_rect.x = PIXELS_PER_UNIT / 2 * (texture_coords[item.type].x());
    clip_rect.y = PIXELS_PER_UNIT / 2 * (texture_coords[item.type].y());
    clip_rect.w = PIXELS_PER_UNIT / 2;
    clip_rect.h = PIXELS_PER_UNIT / 2;

    SDL_Rect dest_rect;
    dest_rect.x =
      PIXELS_PER_UNIT * (item.pos.x() - camera_system.get_pos().x()) + SCREEN_SIZE_X / 2;
    dest_rect.y =
      PIXELS_PER_UNIT * (item.pos.y() - camera_system.get_pos().y()) + SCREEN_SIZE_Y / 2;
    dest_rect.w = PIXELS_PER_UNIT / 2;
    dest_rect.h = PIXELS_PER_UNIT / 2;

    SDL_RenderCopy(
      sdl_interface.renderer,
      textures[texture_name],
      &clip_rect, &dest_rect);
  }
}


void RenderSystem::render()
{
  render_chunk_floors();

  for (int x = 0; x < MAP_SIZE_X; x += TILES_PER_CHUNK_X)
  {
    for (int y = 0; y < MAP_SIZE_Y; y += TILES_PER_CHUNK_Y)
    {
      auto& chunk(map_system.get_chunk(x, y, current_floor));

      render_floor_entities(chunk);
      render_entities(chunk);
      render_items(chunk);
    }
  }

  for (auto& user : entity_system.get_users())
  {
    SDL_Rect dest_rect;
    dest_rect.x =
      PIXELS_PER_UNIT * (user.pos.x() - camera_system.get_pos().x()) + SCREEN_SIZE_X / 2;
    dest_rect.y =
      PIXELS_PER_UNIT * (user.pos.y() - camera_system.get_pos().y()) + SCREEN_SIZE_Y / 2;
    dest_rect.w = PIXELS_PER_UNIT;
    dest_rect.h = PIXELS_PER_UNIT;

    SDL_RenderCopy(
      sdl_interface.renderer,
      textures[type_to_texture_map[user.type]],
      &user.clip_rect, &dest_rect);
  }
}


void RenderSystem::update()
{
  SDL_SetRenderDrawColor(sdl_interface.renderer, 0, 0, 0, 0);
  SDL_RenderClear(sdl_interface.renderer);

  render();

  interface_system.render();
  physics_system.render_debug();
}


void RenderSystem::shutdown()
{
  for (auto& pair : textures)
    SDL_DestroyTexture(pair.second);
}
