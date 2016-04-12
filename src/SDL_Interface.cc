#include "SDL_Interface.h"

#include <iostream>

#include "Utils.h"
#include "constants/RenderConstants.h"
#include "constants/UIConstants.h"

using namespace Eigen;
using namespace std;
using namespace Utils;

namespace ld
{

SDL_Interface::SDL_Interface()
  : window(nullptr),
    renderer(nullptr),
    fonts(),
    surfaces(),
    textures()
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    cout << "SDL_Init error: " << SDL_GetError() << endl;

  window =
    SDL_CreateWindow(
      "Last Ditch", 100, 100, SCREEN_SIZE_X, SCREEN_SIZE_Y, SDL_WINDOW_SHOWN);
  renderer =
    SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  TTF_Init();

  auto img_flags(IMG_INIT_PNG);
  IMG_Init(img_flags);

  load_textures();
}


SDL_Interface::~SDL_Interface()
{
  for (auto& kv : surfaces) SDL_FreeSurface(kv.second);
  for (auto& kv : textures) SDL_DestroyTexture(kv.second);

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  for (auto& kv : fonts) TTF_CloseFont(kv.second);

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}


void SDL_Interface::pre_render()
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
}


void SDL_Interface::post_render()
{
  SDL_RenderPresent(renderer);
}


SDL_Surface* SDL_Interface::load_surface(string name)
{
  auto path("media/textures/" + name + ".png");

  return IMG_Load(path.c_str());
}


void SDL_Interface::load_textures()
{
  load_texture("kadijah");
  load_texture("chunk_floor1");
  load_texture("items1");
  load_texture("tileset1");
  load_texture("ui1");

  load_texture("Jura");
}


void SDL_Interface::load_texture(std::string file_name, std::string texture)
{
  if (texture == "") texture = file_name;

  auto path("media/textures/" + file_name + ".png");

  textures[texture] = IMG_LoadTexture(renderer, path.c_str());
}


SDL_Surface* SDL_Interface::generate_surface(unsigned size_x, unsigned size_y)
{
  SDL_Surface* surface;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  surface = SDL_CreateRGBSurface(
    0, size_x, size_y, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
#else
  surface = SDL_CreateRGBSurface(
    0, size_x, size_y, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
#endif

  return surface;
}


SDL_Surface* SDL_Interface::generate_text_surface(
  std::string text, std::string font, SDL_Color color)
{
  return TTF_RenderText_Blended(fonts[font], text.c_str(), color);
}


SDL_Surface* SDL_Interface::generate_scalable_surface(Scalable& element)
{
  auto surface(generate_surface(element.dest_rect.w, element.dest_rect.h));

  SDL_Rect ct_clip_rect, ct_dest_rect;
  SDL_Rect tt_clip_rect, tt_dest_rect;
  SDL_Rect tl_clip_rect, tl_dest_rect;
  SDL_Rect ll_clip_rect, ll_dest_rect;
  SDL_Rect bl_clip_rect, bl_dest_rect;
  SDL_Rect bb_clip_rect, bb_dest_rect;
  SDL_Rect br_clip_rect, br_dest_rect;
  SDL_Rect rr_clip_rect, rr_dest_rect;
  SDL_Rect tr_clip_rect, tr_dest_rect;

  ct_clip_rect = Scalable_Data[element.type].clip_rects["ct"];
  ct_dest_rect.x = element.border;
  ct_dest_rect.y = element.border;
  tt_clip_rect = Scalable_Data[element.type].clip_rects["tt"];
  tt_dest_rect.x = element.border;
  tt_dest_rect.y = 0;
  tl_clip_rect = Scalable_Data[element.type].clip_rects["tl"];
  tl_dest_rect.x = 0;
  tl_dest_rect.y = 0;
  ll_clip_rect = Scalable_Data[element.type].clip_rects["ll"];
  ll_dest_rect.x = 0;
  ll_dest_rect.y = element.border;
  bl_clip_rect = Scalable_Data[element.type].clip_rects["bl"];
  bl_dest_rect.x = 0;
  bl_dest_rect.y = element.dest_rect.h - element.border;
  bb_clip_rect = Scalable_Data[element.type].clip_rects["bb"];
  bb_dest_rect.x = element.border;
  bb_dest_rect.y = element.dest_rect.h - element.border;
  br_clip_rect = Scalable_Data[element.type].clip_rects["br"];
  br_dest_rect.x = element.dest_rect.w - element.border;
  br_dest_rect.y = element.dest_rect.h - element.border;
  rr_clip_rect = Scalable_Data[element.type].clip_rects["rr"];
  rr_dest_rect.x = element.dest_rect.w - element.border;
  rr_dest_rect.y = element.border;
  tr_clip_rect = Scalable_Data[element.type].clip_rects["tr"];
  tr_dest_rect.x = element.dest_rect.w - element.border;
  tr_dest_rect.y = 0;

  auto source_surface(surfaces[element.source_texture]);

  SDL_BlitSurface(source_surface, &ct_clip_rect, surface, &ct_dest_rect);
  SDL_BlitSurface(source_surface, &tt_clip_rect, surface, &tt_dest_rect);
  SDL_BlitSurface(source_surface, &tl_clip_rect, surface, &tl_dest_rect);
  SDL_BlitSurface(source_surface, &ll_clip_rect, surface, &ll_dest_rect);
  SDL_BlitSurface(source_surface, &bl_clip_rect, surface, &bl_dest_rect);
  SDL_BlitSurface(source_surface, &bb_clip_rect, surface, &bb_dest_rect);
  SDL_BlitSurface(source_surface, &br_clip_rect, surface, &br_dest_rect);
  SDL_BlitSurface(source_surface, &rr_clip_rect, surface, &rr_dest_rect);
  SDL_BlitSurface(source_surface, &tr_clip_rect, surface, &tr_dest_rect);

  return surface;
}


void SDL_Interface::generate_label(Label& element)
{
}


void SDL_Interface::generate_button(Button& element)
{
}


void SDL_Interface::generate_window(Window& element)
{
}


void SDL_Interface::generate_list(List& element)
{
  auto list_surface(generate_surface(element.dest_rect.w, element.dest_rect.h));

  for (auto i(0); i < element.entries.size(); ++i)
  {
    SDL_Color color;

    if (i == element.index) color = element.selected_entry_color;
    else color = element.normal_entry_color;

    auto entry_surface(
      generate_text_surface(element.entries[i], element.font, color));

    SDL_Rect dest_rect;
    dest_rect.x = 0;
    dest_rect.y = entry_surface->h * i + element.offset;

    SDL_BlitSurface(entry_surface, nullptr, list_surface, &dest_rect);
    SDL_FreeSurface(entry_surface);
  }

}


void SDL_Interface::generate_texture(SDL_Surface* surface, std::string texture)
{
  if (textures[texture]) SDL_DestroyTexture(textures[texture]);
  textures[texture] = SDL_CreateTextureFromSurface(renderer, surface);
}


void SDL_Interface::render_chunk(Chunk& chunk)
{
  SDL_Rect dest_rect;
  dest_rect.x = PIXELS_PER_UNIT * (chunk.pos.x() - camera_position.x());
  dest_rect.y = PIXELS_PER_UNIT * (chunk.pos.y() - camera_position.y());
  dest_rect.w = PIXELS_PER_UNIT * TILES_PER_CHUNK_X;
  dest_rect.h = PIXELS_PER_UNIT * TILES_PER_CHUNK_Y;

  SDL_RenderCopy(renderer, textures[chunk.texture], nullptr, &dest_rect);
}


void SDL_Interface::render_item(Item& item)
{
  SDL_Rect dest_rect;
  dest_rect.x = PIXELS_PER_UNIT * (item.pos.x() - camera_position.x());
  dest_rect.y = PIXELS_PER_UNIT * (item.pos.y() - camera_position.y());
  dest_rect.w = HALF_UNIT;
  dest_rect.h = HALF_UNIT;

  SDL_RenderCopy(renderer, textures[item.texture], &item.clip_rect, &dest_rect);
}


void SDL_Interface::render_tile(Tile& tile)
{
  SDL_Rect dest_rect;
  dest_rect.x = PIXELS_PER_UNIT * (tile.pos.x() - camera_position.x());
  dest_rect.y = PIXELS_PER_UNIT * (tile.pos.y() - camera_position.y());
  dest_rect.w = PIXELS_PER_UNIT;
  dest_rect.h = PIXELS_PER_UNIT;

  SDL_RenderCopyEx(
    renderer, textures[tile.texture],
    &tile.clip_rect, &dest_rect,
    90 * tile.direction, nullptr, SDL_FLIP_NONE);
}


void SDL_Interface::render_door(Door& door)
{
  SDL_Rect dest_rect;
  dest_rect.x = PIXELS_PER_UNIT * (door.pos.x() - camera_position.x());
  dest_rect.y = PIXELS_PER_UNIT * (door.pos.y() - camera_position.y());
  dest_rect.w = PIXELS_PER_UNIT;
  dest_rect.h = PIXELS_PER_UNIT;

  SDL_RenderCopyEx(
    renderer, textures[door.texture],
    &door.clip_rect, &dest_rect,
    90 * door.direction, nullptr, SDL_FLIP_NONE);
}


void SDL_Interface::render_user(User& user)
{
  SDL_Rect dest_rect;
  dest_rect.x = PIXELS_PER_UNIT * (user.pos.x() - camera_position.x());
  dest_rect.y = PIXELS_PER_UNIT * (user.pos.y() - camera_position.y());
  dest_rect.w = PIXELS_PER_UNIT;
  dest_rect.h = PIXELS_PER_UNIT;

  SDL_RendererFlip flip(
    ends_with(user.animation, "left") ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);

  SDL_RenderCopyEx(
    renderer, textures[user.texture],
    &user.clip_rect, &dest_rect,
    0, nullptr, flip);
}


void SDL_Interface::render_element(Element& element)
{
  SDL_RenderCopy(
    renderer, textures[element.batch_texture], &element.clip_rect, &element.dest_rect);
}


void SDL_Interface::render_text(std::string text, unsigned x, unsigned y)
{
  auto offset(0);

  for (auto c : text)
  {
    SDL_Rect clip_rect;
    clip_rect = Font_Data[c];

    SDL_Rect dest_rect;
    dest_rect.x = x + offset;
    dest_rect.y = y;
    dest_rect.w = clip_rect.w;
    dest_rect.h = clip_rect.h;

    SDL_RenderCopy(
      renderer, textures["Jura"], &clip_rect, &dest_rect);

    offset += dest_rect.w;
  }
}


}
