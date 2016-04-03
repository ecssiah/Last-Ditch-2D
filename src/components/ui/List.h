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
  {
    entry_color.r = 200;
    entry_color.g = 200;
    entry_color.b = 200;
    entry_color.a = 255;

    selected_entry_color.r = 255;
    selected_entry_color.g = 255;
    selected_entry_color.b = 255;
    selected_entry_color.a = 255;
  }

  int offset;
  unsigned index;
  std::string font;

  SDL_Color entry_color;
  SDL_Color selected_entry_color;

  std::vector<std::string> entries;
};

}

#endif /* LIST_H */
