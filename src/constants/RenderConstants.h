#ifndef RENDERCONSTANTS_H
#define RENDERCONSTANTS_H

namespace ld
{

constexpr unsigned PIXELS_PER_UNIT(48);
constexpr unsigned HALF_UNIT(PIXELS_PER_UNIT / 2);
constexpr unsigned SCREEN_SIZE_X(800);
constexpr unsigned SCREEN_SIZE_Y(600);
constexpr unsigned HALF_SCREEN_SIZE_X(SCREEN_SIZE_X / 2);
constexpr unsigned HALF_SCREEN_SIZE_Y(SCREEN_SIZE_Y / 2);
constexpr float HALF_SCREEN_SIZE_X_WORLD(HALF_SCREEN_SIZE_X / (float)PIXELS_PER_UNIT);
constexpr float HALF_SCREEN_SIZE_Y_WORLD(HALF_SCREEN_SIZE_Y / (float)PIXELS_PER_UNIT);

}

#endif /* RENDERCONSTANTS_H */
