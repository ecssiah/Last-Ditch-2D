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
#include "components/ScalableElement.h"
#include "components/ScrollableElement.h"
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

  void set_camera_pos(Eigen::Vector2f _cam_pos) { cam_pos = _cam_pos; }

  SDL_Surface* generate_surface(unsigned size_x, unsigned size_y);

  void generate_text_element(TextElement& element);
  void generate_list_element(ListElement& element);

  void create_texture_from_text(
    std::string text, std::string texture_name,
    std::string font_name = "jura-small",
    SDL_Color color = {220, 255, 255});

  SDL_Surface* create_surface_from_text(
    std::string text, std::string font_name, SDL_Color color);

  void render_chunk(Chunk& chunk);
  void render_item(Item& item);
  void render_tile(Tile& tile);
  void render_door(Door& door);
  void render_user(User& user);

  void render_ui_element(UIElement& element);
  void render_text_element(TextElement& element);
  void render_scalable_element(ScalableElement& element);
  void render_scrollable_element(ScrollableElement& element);
  void render_list_element(ListElement& element);
  void render_button(ButtonElement& element);

  SDL_Window* window;
  SDL_Renderer* renderer;

  std::unordered_map<std::string, TTF_Font*> fonts;
  std::unordered_map<std::string, SDL_Texture*> textures;

};

}

#endif /* SDL_INTERFACE_H */
