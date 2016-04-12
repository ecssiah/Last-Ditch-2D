#ifndef SDL_INTERFACE_H
#define SDL_INTERFACE_H

#include <eigen3/Eigen/Geometry>
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
#include "components/ui/Scalable.h"
#include "components/ui/Text.h"
#include "components/ui/Window.h"
#include "components/Tile.h"
#include "components/User.h"

namespace ld
{

class SDL_Interface
{
  void load_fonts();
  void load_textures();

  SDL_Surface* load_surface(std::string name);
  void load_texture(std::string file_name, std::string texture = std::string());

  Eigen::Vector2f camera_position;

public:
  SDL_Interface();
  ~SDL_Interface();

  void pre_render();
  void post_render();

  void generate_tile(Tile& tile);
  void generate_user(User& user);

  SDL_Surface* generate_surface(unsigned size_x, unsigned size_y);
  SDL_Surface* generate_text_surface(std::string text, std::string font, SDL_Color color);
  SDL_Surface* generate_scalable_surface(Scalable& element);

  void generate_label(Label& element);
  void generate_button(Button& element);
  void generate_window(Window& element);
  void generate_list(List& element);

  SDL_Rect batch_element(Element& element);

  void generate_texture(SDL_Surface* surface, std::string texture);

  void render_chunk(Chunk& chunk);
  void render_item(Item& item);
  void render_tile(Tile& tile);
  void render_door(Door& door);
  void render_user(User& user);

  void render_element(Element& element);
  void render_text(std::string text, unsigned x, unsigned y);

  inline void set_camera_position(
    Eigen::Vector2f _camera_position) { camera_position = _camera_position; }

  SDL_Window* window;
  SDL_Renderer* renderer;

  std::unordered_map<std::string, TTF_Font*> fonts;
  std::unordered_map<std::string, SDL_Surface*> surfaces;
  std::unordered_map<std::string, SDL_Texture*> textures;
};

}

#endif /* SDL_INTERFACE_H */
