#include "SDL_Interface.h"

#include "Utils.h"
#include "constants/RenderConstants.h"
#include "constants/UIConstants.h"

using namespace Eigen;
using namespace ld;
using namespace std;
using namespace Utils;


SDL_Surface* generate_surface(unsigned size_x, unsigned size_y)
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


void SDL_Interface::generate_text_element(TextElement& element)
{
  create_texture_from_text(
    element.text, element.text_texture, element.text_font, element.text_color);
}


void SDL_Interface::generate_list_element(ListElement& element)
{

}


void SDL_Interface::generate_list_texture()
{
  set<Item> unique_items;
  unordered_map<string, unsigned> item_counts;

  for (auto& item : inventory.items)
  {
    ++item_counts[item.type];

    if (active_category == ALL || item.category == active_category)
      unique_items.insert(item);
  }

  current_slots.clear();
  vector<Item> items(unique_items.begin(), unique_items.end());

  for (auto i(0); i < items.size(); ++i)
  {
    auto& item(items[i]);
    auto& name(item.name);
    auto& item_count(item_counts[item.type]);

    if (item_count != 1) name += " (" + to_string(item_count) + ")";

    SDL_Color color;

    if (i == active_slot_index)
      color = {255, 255, 255};
    else
      color = {200, 180, 200};

    auto surface(create_surface_from_text(name, "jura-small", color));
    element_surfaces.push_back(surface);

    current_slots.push_back({(unsigned)i, item_count, item.type});
  }
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
  chunk.dest_rect.x = PIXELS_PER_UNIT * (chunk.pos.x() - cam_pos.x()) + HALF_SCREEN_SIZE_X;
  chunk.dest_rect.y = PIXELS_PER_UNIT * (chunk.pos.y() - cam_pos.y()) + HALF_SCREEN_SIZE_Y;

  SDL_RenderCopy(renderer, textures[chunk.texture], nullptr, &chunk.dest_rect);
}


void SDL_Interface::render_item(Item& item)
{
  item.dest_rect.x = PIXELS_PER_UNIT * (item.pos.x() - cam_pos.x()) + HALF_SCREEN_SIZE_X;
  item.dest_rect.y = PIXELS_PER_UNIT * (item.pos.y() - cam_pos.y()) + HALF_SCREEN_SIZE_Y;

  SDL_RenderCopy(renderer, textures[item.texture], &item.clip_rect, &item.dest_rect);
}


void SDL_Interface::render_tile(Tile& tile)
{
  tile.dest_rect.x = PIXELS_PER_UNIT * (tile.pos.x() - cam_pos.x()) + HALF_SCREEN_SIZE_X;
  tile.dest_rect.y = PIXELS_PER_UNIT * (tile.pos.y() - cam_pos.y()) + HALF_SCREEN_SIZE_Y;

  SDL_RenderCopyEx(
    renderer, textures[tile.texture],
    &tile.clip_rect, &tile.dest_rect,
    tile.rotation, nullptr, SDL_FLIP_NONE);
}


void SDL_Interface::render_door(Door& door)
{
  door.dest_rect.x = PIXELS_PER_UNIT * (door.pos.x() - cam_pos.x()) + HALF_SCREEN_SIZE_X;
  door.dest_rect.y = PIXELS_PER_UNIT * (door.pos.y() - cam_pos.y()) + HALF_SCREEN_SIZE_Y;

  SDL_RenderCopy(renderer, textures[door.texture], &door.clip_rect, &door.dest_rect);
}


void SDL_Interface::render_user(User& user)
{
  user.dest_rect.x = PIXELS_PER_UNIT * (user.pos.x() - cam_pos.x()) + HALF_SCREEN_SIZE_X;
  user.dest_rect.y = PIXELS_PER_UNIT * (user.pos.y() - cam_pos.y()) + HALF_SCREEN_SIZE_Y;

  if (user.frame % 2 == 0) ++user.dest_rect.y;

  SDL_RendererFlip flip(
    ends_with(user.animation, "left") ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
  SDL_RendererFlip arm_flip(
    ends_with(user.arm_animation, "left") ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);

  SDL_RenderCopyEx(
    renderer, textures[user.texture],
    &user.clip_rect, &user.dest_rect,
    0, nullptr, flip);

  SDL_RenderCopyEx(
    renderer, textures[user.arm_texture],
    &user.arm_clip_rect, &user.dest_rect,
    0, nullptr, arm_flip);
}


void SDL_Interface::render_ui_element(UIElement& ui_element)
{
  ui_element.dest_rect.x = ui_element.pos.x();
  ui_element.dest_rect.y = ui_element.pos.y();

  SDL_RenderCopy(
    renderer, textures[ui_element.texture],
    &ui_element.clip_rect, &ui_element.dest_rect);
}


void SDL_Interface::render_text_element(TextElement& text_element)
{
  if (text_element.texture != "")
    render_ui_element(text_element);

  text_element.text_dest_rect.x = text_element.pos.x();
  text_element.text_dest_rect.y = text_element.pos.y();

  SDL_RenderCopy(
    renderer, textures[text_element.text_texture],
    &text_element.text_clip_rect, &text_element.text_dest_rect);
}


void SDL_Interface::render_scalable_element(ScalableElement& scalable_element)
{
  scalable_element.dest_rect.x = scalable_element.pos.x();
  scalable_element.dest_rect.y = scalable_element.pos.y();

  SDL_RenderCopy(
    renderer, textures[scalable_element.texture], nullptr, &scalable_element.dest_rect);
}


void SDL_Interface::render_scrollable_element(ScrollableElement& element)
{
  element.dest_rect.x = element.pos.x();
  element.dest_rect.y = element.pos.y();

  SDL_RenderCopy(renderer, textures[element.texture], nullptr, &element.dest_rect);
}


void SDL_Interface::render_button(ButtonElement& button_element)
{


}
