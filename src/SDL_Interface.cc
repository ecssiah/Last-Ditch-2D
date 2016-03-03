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
  fonts["jura-medium"] = TTF_OpenFont("media/fonts/JuraMedium.ttf", 18);
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


void SDL_Interface::create_texture_from_text(
  string text, string texture_name, string font_name, SDL_Color color)
{
  auto surface = TTF_RenderText_Blended(fonts[font_name], text.c_str(), color);

  if (textures[texture_name] != nullptr) SDL_DestroyTexture(textures[texture_name]);

  textures[texture_name] = SDL_CreateTextureFromSurface(renderer, surface);
}


void SDL_Interface::render_element(UIElement& element)
{
  if (element.texture != "")
  {
    auto& texture(textures[element.texture]);

    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

    SDL_Rect dest_rect;
    dest_rect.x = element.pos.x();
    dest_rect.y = element.pos.y();
    dest_rect.w = element.size.x();
    dest_rect.h = element.size.y();

    SDL_RenderCopy(renderer, texture, nullptr, &dest_rect);
  }

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


void SDL_Interface::render_scalable_element(ScalableElement& element)
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


void SDL_Interface::render_scalable_sub_element(ScalableElement& element, string sub_element)
{
  auto& clip_data(ELEMENT_INFO[element.type + sub_element].clip_data);

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

  for (auto i(0); i < element.list_elements.size(); ++i)
  {
    auto& list_element(element.list_elements[i]);

    int w, h;
    SDL_QueryTexture(textures[list_element.texture], nullptr, nullptr, &w, &h);

    dest_rect.x = element.pos.x() + 6;
    dest_rect.y = element.pos.y() + 6 + i * h;
    dest_rect.w = w;
    dest_rect.h = h;

    SDL_RenderCopy(renderer, textures[list_element.texture], nullptr, &dest_rect);
  }
}
