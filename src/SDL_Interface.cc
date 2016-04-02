#include "SDL_Interface.h"

#include "constants/RenderConstants.h"
#include "constants/UIConstants.h"

using namespace ld;
using namespace std;

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

  setup_fonts();
  setup_textures();
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


void SDL_Interface::setup_fonts()
{
  fonts["jura-small"] = TTF_OpenFont("media/fonts/JuraMedium.ttf", 14);
  fonts["jura-medium"] = TTF_OpenFont("media/fonts/JuraMedium.ttf", 20);
}


SDL_Texture* SDL_Interface::load_texture(string name)
{
  auto path("media/textures/" + name + ".png");

  return IMG_LoadTexture(renderer, path.c_str());
}


void SDL_Interface::setup_textures()
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


void SDL_Interface::create_texture_from_text(
  string text, string texture_name, string font_name, SDL_Color color)
{
  auto surface(TTF_RenderText_Blended(fonts[font_name], text.c_str(), color));

  if (textures[texture_name] != nullptr) SDL_DestroyTexture(textures[texture_name]);

  textures[texture_name] = SDL_CreateTextureFromSurface(renderer, surface);
}


SDL_Surface* SDL_Interface::create_surface_from_text(
  string text, string font_name, SDL_Color color)
{
  return TTF_RenderText_Blended(fonts[font_name], text.c_str(), color);
}


void SDL_Interface::render_chunk(Chunk& chunk)
{
  SDL_Rect dest_rect;
  dest_rect.x =
    PIXELS_PER_UNIT * (chunk.pos.x() - camera_system.get_pos().x()) + HALF_SCREEN_SIZE_X;
  dest_rect.y =
    PIXELS_PER_UNIT * (chunk.pos.y() - camera_system.get_pos().y()) + HALF_SCREEN_SIZE_Y;
  dest_rect.w = PIXELS_PER_UNIT * TILES_PER_CHUNK_X;
  dest_rect.h = PIXELS_PER_UNIT * TILES_PER_CHUNK_Y;

  SDL_RenderCopy(
    sdl_interface.renderer,
    sdl_interface.textures[chunk.texture],
    nullptr, &dest_rect);
}


void SDL_Interface::render_item(Item& item)
{
  auto& clip_data(ITEM_INFO[item.type].clip_data);

  SDL_Rect clip_rect;
  clip_rect.x = clip_data.x;
  clip_rect.y = clip_data.y;
  clip_rect.w = clip_data.w;
  clip_rect.h = clip_data.h;

  SDL_Rect dest_rect;
  dest_rect.x =
    PIXELS_PER_UNIT * (item.pos.x() - camera_system.get_pos().x()) + HALF_SCREEN_SIZE_X;
  dest_rect.y =
    PIXELS_PER_UNIT * (item.pos.y() - camera_system.get_pos().y()) + HALF_SCREEN_SIZE_Y;
  dest_rect.w = PIXELS_PER_UNIT / 2;
  dest_rect.h = PIXELS_PER_UNIT / 2;

  SDL_RenderCopy(
    sdl_interface.renderer,
    sdl_interface.textures[item.texture],
    &clip_rect, &dest_rect);
}


void SDL_Interface::render_tile(Tile& tile)
{
  auto& clip_data(TILE_INFO[tile.type].clip_data);

  SDL_Rect clip_rect;
  clip_rect.x = clip_data.x;
  clip_rect.y = clip_data.y;
  clip_rect.w = clip_data.w;
  clip_rect.h = clip_data.h;

  SDL_Rect dest_rect;
  dest_rect.x =
    PIXELS_PER_UNIT * (tile.pos.x() - camera_system.get_pos().x()) + HALF_SCREEN_SIZE_X;
  dest_rect.y =
    PIXELS_PER_UNIT * (tile.pos.y() - camera_system.get_pos().y()) + HALF_SCREEN_SIZE_Y;
  dest_rect.w = PIXELS_PER_UNIT;
  dest_rect.h = PIXELS_PER_UNIT;

  SDL_RenderCopyEx(
    sdl_interface.renderer,
    sdl_interface.textures[tile.texture],
    &clip_rect, &dest_rect,
    tile.rotation,
    nullptr,
    SDL_FLIP_NONE);
}


void SDL_Interface::render_door(Door& door)
{
  auto& clip_data(TILE_INFO[door.type + (door.open ? "-open" : "-closed")].clip_data);

  SDL_Rect clip_rect;
  clip_rect.x = clip_data.x;
  clip_rect.y = clip_data.y;
  clip_rect.w = clip_data.w;
  clip_rect.h = clip_data.h;

  SDL_Rect dest_rect;
  dest_rect.x =
    PIXELS_PER_UNIT * (door.pos.x() - camera_system.get_pos().x()) + HALF_SCREEN_SIZE_X;
  dest_rect.y =
    PIXELS_PER_UNIT * (door.pos.y() - camera_system.get_pos().y()) + HALF_SCREEN_SIZE_Y;
  dest_rect.w = PIXELS_PER_UNIT;
  dest_rect.h = PIXELS_PER_UNIT;

  SDL_RenderCopy(
    sdl_interface.renderer,
    sdl_interface.textures[door.texture],
    &clip_rect, &dest_rect);
}


void SDL_Interface::render_user(User& user)
{
  SDL_Rect dest_rect;
  dest_rect.x =
    PIXELS_PER_UNIT * (user.pos.x() - camera_system.get_pos().x()) + HALF_SCREEN_SIZE_X;
  dest_rect.y =
    PIXELS_PER_UNIT * (user.pos.y() - camera_system.get_pos().y()) + HALF_SCREEN_SIZE_Y;
  dest_rect.w = PIXELS_PER_UNIT;
  dest_rect.h = PIXELS_PER_UNIT;

  SDL_RendererFlip flip(
    ends_with(user.animation, "left") ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);

  SDL_RenderCopyEx(
    sdl_interface.renderer,
    sdl_interface.textures[user.texture],
    &user.clip_rect, &dest_rect,
    0,
    nullptr,
    flip);

  SDL_RendererFlip arm_flip(
    ends_with(user.arm_animation, "left") ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);

  if (user.frame % 2 == 0) ++dest_rect.y;

  SDL_RenderCopyEx(
    sdl_interface.renderer,
    sdl_interface.textures[user.arm_texture],
    &user.arm_clip_rect, &dest_rect,
    0,
    nullptr,
    arm_flip);
}


void SDL_Interface::render_ui_element(UIElement& ui_element)
{
  auto& texture(textures[ui_element.texture]);

  SDL_Rect dest_rect;
  dest_rect.x = ui_element.pos.x();
  dest_rect.y = ui_element.pos.y();
  dest_rect.w = ui_element.size.x();
  dest_rect.h = ui_element.size.y();

  SDL_RenderCopy(renderer, texture, &ui_element.clip_rect, &dest_rect);
}


void SDL_Interface::render_scalable_element(ScalableElement& scalable_element)
{
  render_scalable_sub_element(element, "ct");
  render_scalable_sub_element(element, "tl");
  render_scalable_sub_element(element, "tt");
  render_scalable_sub_element(element, "tr");
  render_scalable_sub_element(element, "rr");
  render_scalable_sub_element(element, "br");
  render_scalable_sub_element(element, "bb");
  render_scalable_sub_element(element, "bl");
  render_scalable_sub_element(element, "ll");

  if (element.text_texture != "")
  {
    auto& text_texture(textures[element.text_texture]);

    int tw, th;
    SDL_QueryTexture(text_texture, nullptr, nullptr, &tw, &th);

    SDL_Rect text_dest_rect;
    text_dest_rect.x = element.pos.x() + (element.size.x() - tw) / 2;
    text_dest_rect.y = element.pos.y() + (element.size.y() - th) / 2;
    text_dest_rect.w = tw;
    text_dest_rect.h = th;

    SDL_RenderCopy(renderer, text_texture, nullptr, &text_dest_rect);
  }

}


void SDL_Interface::render_scalable_element(ScalableElement& scalable_element)
{
  auto& clip_data(ELEMENT_INFO[element.type + "-" + sub_element].clip_data);

  ElementInfoData[element

  SDL_Rect clip_rect;
  clip_rect.x = clip_data.x;
  clip_rect.y = clip_data.y;
  clip_rect.w = clip_data.w;
  clip_rect.h = clip_data.h;

  SDL_Rect dest_rect;
  if (sub_element == "ct")
  {
    dest_rect.x = element.pos.x() + element.border;
    dest_rect.y = element.pos.y() + element.border;
    dest_rect.w = element.size.x() - 2 * element.border;
    dest_rect.h = element.size.y() - 2 * element.border;
  }
  else if (sub_element == "tr")
  {
    dest_rect.x = element.pos.x() + element.size.x() - element.border;
    dest_rect.y = element.pos.y();
    dest_rect.w = clip_data.w;
    dest_rect.h = clip_data.h;
  }
  else if (sub_element == "br")
  {
    dest_rect.x = element.pos.x() + element.size.x() - element.border;
    dest_rect.y = element.pos.y() + element.size.y() - element.border;
    dest_rect.w = clip_data.w;
    dest_rect.h = clip_data.h;
  }
  else if (sub_element == "bl")
  {
    dest_rect.x = element.pos.x();
    dest_rect.y = element.pos.y() + element.size.y() - element.border;
    dest_rect.w = clip_data.w;
    dest_rect.h = clip_data.h;
  }
  else if (sub_element == "tl")
  {
    dest_rect.x = element.pos.x();
    dest_rect.y = element.pos.y();
    dest_rect.w = clip_data.w;
    dest_rect.h = clip_data.h;
  }
  else if (sub_element == "tt")
  {
    dest_rect.x = element.pos.x() + element.border;
    dest_rect.y = element.pos.y();
    dest_rect.w = element.size.x() - 2 * element.border;
    dest_rect.h = clip_data.h;
  }
  else if (sub_element == "rr")
  {
    dest_rect.x = element.pos.x() + element.size.x() - element.border;
    dest_rect.y = element.pos.y() + element.border;
    dest_rect.w = clip_data.w;
    dest_rect.h = element.size.y() - 2 * element.border;
  }
  else if (sub_element == "bb")
  {
    dest_rect.x = element.pos.x() + element.border;
    dest_rect.y = element.pos.y() + element.size.y() - element.border;
    dest_rect.w = element.size.x() - 2 * element.border;
    dest_rect.h = clip_data.h;
  }
  else if (sub_element == "ll")
  {
    dest_rect.x = element.pos.x();
    dest_rect.y = element.pos.y() + element.border;
    dest_rect.w = clip_data.w;
    dest_rect.h = element.size.y() - 2 * element.border;
  }

  SDL_RenderCopy(renderer, textures[element.texture], &clip_rect, &dest_rect);


}


void SDL_Interface::render_scrollable_element(ScrollableElement& element)
{
  SDL_Rect dest_rect;
  dest_rect.x = element.pos.x();
  dest_rect.y = element.pos.y();
  dest_rect.w = element.size.x();
  dest_rect.h = element.size.y();

  SDL_RenderCopy(renderer, textures[element.texture], nullptr, &dest_rect);
}


void SDL_Interface::render_button(ButtonElement& button_element)
{


}
