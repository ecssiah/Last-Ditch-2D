#ifndef UICONSTANTS_H
#define UICONSTANTS_H

#include <string>
#include <unordered_map>

#include "../components/info/ScalableInfo.h"

namespace ld
{

extern const unsigned BASE_WINDOW_SIZE_X;
extern const unsigned BASE_WINDOW_SIZE_Y;
extern const unsigned MENU_BUTTON_SIZE_X;
extern const unsigned MENU_BUTTON_SIZE_Y;

extern const float INVENTORY_MOUSE_SCROLL_RATE;
extern const float INVENTORY_WHEEL_SCROLL_RATE;

extern std::unordered_map<std::string, ScalableInfo> Scalable_Data;

}

#endif /* UICONSTANTS_H */
