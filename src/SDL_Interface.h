#ifndef SDL_INTERFACE_H
#define SDL_INTERFACE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <unordered_map>

#include "components/UIElement.h"
#include "components/ScalableElement.h"
#include "components/ScrollableElement.h"

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

  void create_texture_from_text(
    std::string text, std::string texture_name, std::string font_name = "jura-small");

  void render_element(UIElement& element);
  void render_scalable_element(ScalableElement& element);
  void render_scalable_sub_element(ScalableElement& element, std::string sub_element);
  void render_scrollable_element(ScrollableElement& element);

  SDL_Window* window;
  SDL_Renderer* renderer;

  std::unordered_map<std::string, TTF_Font*> fonts;
  std::unordered_map<std::string, SDL_Texture*> textures;

};

}

#endif /* SDL_INTERFACE_H */
