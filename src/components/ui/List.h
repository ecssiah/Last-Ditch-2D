#ifndef LIST_H
#define LIST_H

#include <SDL2/SDL.h>
#include <string>

#include "Element.h"

using namespace std;

namespace ld
{

struct List : public Element
{
  List()
    : Element(),
      font("jura-small")
  {
    normal_entry_color.r = 200;
    normal_entry_color.g = 200;
    normal_entry_color.b = 200;
    normal_entry_color.a = 255;

    selected_entry_color.r = 255;
    selected_entry_color.g = 255;
    selected_entry_color.b = 255;
    selected_entry_color.a = 255;
  }

  int offset;
  unsigned index;
  std::string font;

  SDL_Color normal_entry_color;
  SDL_Color selected_entry_color;

  std::vector<std::string> entries;
};

}

#endif /* LIST_H */
