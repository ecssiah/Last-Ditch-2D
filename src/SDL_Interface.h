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
  void setup_fonts();
  void setup_textures();

  SDL_Texture* load_texture(std::string name);

public:
  SDL_Interface();
  ~SDL_Interface();

  SDL_Surface* generate_surface(unsigned size_x, unsigned size_y);
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

  void render_ui_element(UIElement& ui_element);
  void render_scalable_element(ScalableElement& scalable_element);
  void render_scrollable_element(ScrollableElement& scrollable_element);
  void render_button(ButtonElement& button_element);

  SDL_Window* window;
  SDL_Renderer* renderer;

  std::unordered_map<std::string, TTF_Font*> fonts;
  std::unordered_map<std::string, SDL_Texture*> textures;

};

}

#endif /* SDL_INTERFACE_H */
