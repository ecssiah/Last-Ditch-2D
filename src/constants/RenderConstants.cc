#include "RenderConstants.h"

namespace ld
{

const unsigned PIXELS_PER_UNIT(64);
const unsigned HALF_UNIT(PIXELS_PER_UNIT / 2);
const unsigned SCREEN_SIZE_X(800);
const unsigned SCREEN_SIZE_Y(600);
const unsigned HALF_SCREEN_SIZE_X(SCREEN_SIZE_X / 2);
const unsigned HALF_SCREEN_SIZE_Y(SCREEN_SIZE_Y / 2);
const float HALF_SCREEN_SIZE_X_WORLD(HALF_SCREEN_SIZE_X / (float)PIXELS_PER_UNIT);
const float HALF_SCREEN_SIZE_Y_WORLD(HALF_SCREEN_SIZE_Y / (float)PIXELS_PER_UNIT);

}
