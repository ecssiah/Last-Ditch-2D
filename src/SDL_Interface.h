#ifndef SDL_INTERFACE_H
#define SDL_INTERFACE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <unordered_map>

#include "components/ButtonElement.h"
#include "components/Chunk.h"
#include "components/Door.h"
#include "components/Item.h"
#include "components/ListElement.h"
#include "components/ScalableElement.h"
#include "components/ScrollableElement.h"
#include "components/WindowElement.h"
#include "components/Tile.h"
#include "components/User.h"
#include "components/UIElement.h"

namespace ld
{

class SDL_Interface
{
  SDL_Texture* load_texture(std::string name);

  void load_fonts();
  void load_textures();

  Eigen::Vector2f cam_pos;

public:
  SDL_Interface();
  ~SDL_Interface();

  void pre_render();
  void post_render();

  SDL_Surface* generate_surface_from_text(
    std::string text, std::string font, SDL_Color color);
  void generate_texture_from_text(
    std::string text, std::string texture,
    std::string font = "jura-small",
    SDL_Color color = {220, 255, 255});

  void generate_text_element(TextElement& element);
  void generate_window_element(WindowElement& element);
  void generate_list_element(ListElement& element);
  void generate_button_element(ButtonElement& element);

  void render_chunk(Chunk& chunk);
  void render_item(Item& item);
  void render_tile(Tile& tile);
  void render_door(Door& door);
  void render_user(User& user);

  void render_ui_element(UIElement& element);
  void render_text_element(TextElement& element);
  void render_scalable_element(ScalableElement& element);
  void render_scrollable_element(ScrollableElement& element);
  void render_window_element(WindowElement& element);
  void render_list_element(ListElement& element);
  void render_button_element(ButtonElement& element);

  SDL_Window* window;
  SDL_Renderer* renderer;

  std::unordered_map<std::string, TTF_Font*> fonts;
  std::unordered_map<std::string, SDL_Texture*> textures;

};

}

#endif /* SDL_INTERFACE_H */
