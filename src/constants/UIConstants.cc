#include "UIConstants.h"

namespace ld
{

const unsigned BASE_WINDOW_SIZE_X(680);
const unsigned BASE_WINDOW_SIZE_Y(520);
const unsigned MENU_BUTTON_SIZE_X(120);
const unsigned MENU_BUTTON_SIZE_Y(20);

const float INVENTORY_MOUSE_SCROLL_RATE(2.f);
const float INVENTORY_WHEEL_SCROLL_RATE(10.f);

std::unordered_map<std::string, ScalableInfo> Scalable_Data;

std::unordered_map<std::string, SDL_Rect> Font_Data;

}
