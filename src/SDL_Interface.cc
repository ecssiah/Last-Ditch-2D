#include "SDL_Interface.h"

#include "Utils.h"
#include "constants/RenderConstants.h"
#include "constants/UIConstants.h"

using namespace Eigen;
using namespace ld;
using namespace std;
using namespace Utils;


SDL_Interface::SDL_Interface()
  : window(nullptr),
    renderer(nullptr)
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

  load_fonts();
  load_textures();
}


SDL_Interface::~SDL_Interface()
{
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


SDL_Texture* SDL_Interface::load_texture(string name)
{
  auto path("media/textures/" + name + ".png");

  return IMG_LoadTexture(renderer, path.c_str());
}


void SDL_Interface::load_fonts()
{
  fonts["jura-small"] = TTF_OpenFont("media/fonts/JuraMedium.ttf", 14);
  fonts["jura-medium"] = TTF_OpenFont("media/fonts/JuraMedium.ttf", 20);
}


void SDL_Interface::load_textures()
{
  textures["kadijah"] = load_texture("kadijah");
  textures["chunk_floor1"] = load_texture("chunk_floor1");
  textures["tileset1"] = load_texture("tileset1");
  textures["items1"] = load_texture("items1");
  textures["ui1"] = load_texture("ui1");
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


void SDL_Interface::generate_text_element(Text& element)
{
  generate_texture_from_text(
    element.text, element.text_texture, element.font, element.color);
}


void SDL_Interface::generate_window_element(Window& element)
{

}


void SDL_Interface::generate_list_element(List& element)
{
  SDL_Surface* list_surface(generate_surface(element.dest_rect.w, element.dest_rect.h));

  for (auto i(0); i < element.entries.size(); ++i)
  {
    SDL_Color color;
    if (i == element.index)
      color = element.selected_entry_color;
    else
      color = element.entry_color;

    SDL_Surface* entry_surface(
      TTF_RenderText_Blended(fonts[element.font], element.entries[i].c_str(), color));

    SDL_Rect dest_rect;
    dest_rect.x = element.dest_rect.x;
    dest_rect.y = element.dest_rect.y + i * 20 + element.offset;

    SDL_BlitSurface(entry_surface, nullptr, list_surface, &dest_rect);
    SDL_FreeSurface(entry_surface);
  }

  if (textures[element.texture]) SDL_DestroyTexture(textures[element.texture]);
  textures[element.texture] = SDL_CreateTextureFromSurface(renderer, list_surface);

  SDL_FreeSurface(list_surface);
}


void SDL_Interface::generate_texture_from_text(
  string text, string texture, string font, SDL_Color color)
{
  auto surface(generate_surface_from_text(text, font, color));

  if (textures[texture]) SDL_DestroyTexture(textures[texture]);
  textures[texture] = SDL_CreateTextureFromSurface(renderer, surface);
}


SDL_Surface* SDL_Interface::generate_surface_from_text(
  string text, string font, SDL_Color color)
{
  return TTF_RenderText_Blended(fonts[font], text.c_str(), color);
}


void SDL_Interface::render_chunk(Chunk& chunk)
{
  SDL_RenderCopy(renderer, textures[chunk.texture], nullptr, &chunk.dest_rect);
}


void SDL_Interface::render_item(Item& item)
{
  SDL_RenderCopy(renderer, textures[item.texture], &item.clip_rect, &item.dest_rect);
}


void SDL_Interface::render_tile(Tile& tile)
{
  SDL_RenderCopyEx(
    renderer, textures[tile.texture],
    &tile.clip_rect, &tile.dest_rect,
    tile.rotation, nullptr, SDL_FLIP_NONE);
}


void SDL_Interface::render_door(Door& door)
{
  SDL_RenderCopy(renderer, textures[door.texture], &door.clip_rect, &door.dest_rect);
}


void SDL_Interface::render_user(User& user)
{
  SDL_RendererFlip flip(
    ends_with(user.animation, "left") ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);

  SDL_RenderCopyEx(
    renderer, textures[user.texture],
    &user.clip_rect, &user.dest_rect,
    0, nullptr, flip);
}


void SDL_Interface::render_element(Element& element)
{
  SDL_RenderCopy(
    renderer, textures[element.texture],
    &element.clip_rect, &element.dest_rect);
}


void SDL_Interface::render_text_element(Text& element)
{
  if (element.texture != "") render_element(element);

  SDL_RenderCopy(
    renderer, textures[element.text_texture],
    &element.text_clip_rect, &element.text_dest_rect);
}


void SDL_Interface::render_button_element(Button& element)
{


}


void SDL_Interface::render_window_element(Window& element)
{
  SDL_RenderCopy(renderer, textures[element.texture], nullptr, &element.dest_rect);
}
