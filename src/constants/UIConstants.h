#ifndef UICONSTANTS_H
#define UICONSTANTS_H

#include <string>
#include <unordered_map>

#include "../components/ClipData.h"

namespace ld
{

constexpr unsigned MENU_BASE_SIZE_X(680);
constexpr unsigned MENU_BASE_SIZE_Y(520);
constexpr unsigned MENU_BUTTON_SIZE_X(120);
constexpr unsigned MENU_BUTTON_SIZE_Y(20);

constexpr float INVENTORY_MOUSE_SCROLL_RATE(2.f);
constexpr float INVENTORY_WHEEL_SCROLL_RATE(10.f);


struct ElementInfo
{
  ElementInfo() = default;

  ElementInfo(std::string _texture, ClipData _clip_data)
    : texture(_texture),
      clip_data(_clip_data)
  {}

  std::string texture;
  ClipData clip_data;
};


static std::unordered_map<std::string, ElementInfo>
ELEMENT_INFO(
{
  // backdrop1
  {"backdrop1-ct",
    {
      "ui1",
      {4, 4, 32, 16}
    }
  },
  {"backdrop1-tl",
    {
      "ui1",
      {0, 0, 3, 3}
    }
  },
  {"backdrop1-tt",
    {
      "ui1",
      {4, 0, 32, 3}
    }
  },
  {"backdrop1-tr",
    {
      "ui1",
      {37, 0, 3, 3}
    }
  },
  {"backdrop1-rr",
    {
      "ui1",
      {37, 4, 3, 16}
    }
  },
  {"backdrop1-br",
    {
      "ui1",
      {37, 21, 3, 3}
    }
  },
  {"backdrop1-bb",
    {
      "ui1",
      {4, 21, 3, 3}
    }
  },
  {"backdrop1-bl",
    {
      "ui1",
      {0, 21, 3, 3}
    }
  },
  {"backdrop1-ll",
    {
      "ui1",
      {0, 4, 3, 16}
    }
  },
  // button1
  {"button1-ct",
    {
      "ui1",
      {5, 30, 20, 11}
    }
  },
  {"button1-tl",
    {
      "ui1",
      {0, 25, 4, 4}
    }
  },
  {"button1-tt",
    {
      "ui1",
      {5, 25, 20, 4}
    }
  },
  {"button1-tr",
    {
      "ui1",
      {26, 25, 4, 4}
    }
  },
  {"button1-rr",
    {
      "ui1",
      {26, 30, 4, 11}
    }
  },
  {"button1-br",
    {
      "ui1",
      {26, 42, 4, 4}
    }
  },
  {"button1-bb",
    {
      "ui1",
      {5, 42, 20, 4}
    }
  },
  {"button1-bl",
    {
      "ui1",
      {0, 42, 4, 4}
    }
  },
  {"button1-ll",
    {
      "ui1",
      {0, 30, 4, 11}
    }
  },
  // window1
  {"window1-ct",
    {
      "ui1",
      {43, 2, 12, 12}
    }
  },
  {"window1-tl",
    {
      "ui1",
      {41, 0, 1, 1}
    }
  },
  {"window1-tt",
    {
      "ui1",
      {43, 0, 12, 1}
    }
  },
  {"window1-tr",
    {
      "ui1",
      {56, 0, 1, 1}
    }
  },
  {"window1-rr",
    {
      "ui1",
      {56, 2, 1, 12}
    }
  },
  {"window1-br",
    {
      "ui1",
      {56, 15, 1, 1}
    }
  },
  {"window1-bb",
    {
      "ui1",
      {43, 15, 12, 1}
    }
  },
  {"window1-bl",
    {
      "ui1",
      {41, 15, 1, 1}
    }
  },
  {"window1-ll",
    {
      "ui1",
      {41, 2, 1, 12}
    }
  },
});

}

#endif /* UICONSTANTS_H */
