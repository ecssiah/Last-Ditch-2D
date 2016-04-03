#ifndef UICONSTANTS_H
#define UICONSTANTS_H

#include <string>
#include <unordered_map>

#include "../components/info/ElementInfo.h"

namespace ld
{

constexpr unsigned BASE_WINDOW_SIZE_X(680);
constexpr unsigned BASE_WINDOW_SIZE_Y(520);
constexpr unsigned MENU_BUTTON_SIZE_X(120);
constexpr unsigned MENU_BUTTON_SIZE_Y(20);

constexpr float INVENTORY_MOUSE_SCROLL_RATE(2.f);
constexpr float INVENTORY_WHEEL_SCROLL_RATE(10.f);

static std::unordered_map<std::string, ElementInfo> Element_Data;

}

#endif /* UICONSTANTS_H */
