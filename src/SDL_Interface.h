#ifndef SDL_INTERFACE_H
#define SDL_INTERFACE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <unordered_map>

#include "components/Chunk.h"
#include "components/Door.h"
#include "components/Item.h"
#include "components/ui/Button.h"
#include "components/ui/Element.h"
#include "components/ui/List.h"
#include "components/ui/Text.h"
#include "components/ui/Window.h"
#include "components/Tile.h"
#include "components/User.h"

namespace ld
{

class SDL_Interface
{
  SDL_Texture* load_texture(std::string name);
  SDL_Surface* generate_surface(unsigned size_x, unsigned size_y);

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

  void generate_text_element(Text& element);
  void generate_window_element(Window& element);
  void generate_button_element(Button& element);
  void generate_list_element(List& element);

  void render_chunk(Chunk& chunk);
  void render_item(Item& item);
  void render_tile(Tile& tile);
  void render_door(Door& door);
  void render_user(User& user);

  void render_element(Element& element);
  void render_text_element(Text& element);
  void render_window_element(Window& element);
  void render_button_element(Button& element);
  void render_list_element(List& element);

  SDL_Window* window;
  SDL_Renderer* renderer;

  std::unordered_map<std::string, TTF_Font*> fonts;
  std::unordered_map<std::string, SDL_Texture*> textures;

};

}

#endif /* SDL_INTERFACE_H */
