#ifndef RENDERCONSTANTS_H
#define RENDERCONSTANTS_H

#include <eigen3/Eigen/Geometry>
#include <map>
#include <string>
#include <unordered_map>

#include "../components/AnimationData.h"

namespace ld
{

constexpr unsigned PIXELS_PER_UNIT(48);
constexpr unsigned SCREEN_SIZE_X(800);
constexpr unsigned SCREEN_SIZE_Y(600);
constexpr unsigned HALF_SCREEN_SIZE_X(SCREEN_SIZE_X / 2);
constexpr unsigned HALF_SCREEN_SIZE_Y(SCREEN_SIZE_Y / 2);
constexpr float HALF_SCREEN_SIZE_X_WORLD(HALF_SCREEN_SIZE_X / (float)PIXELS_PER_UNIT);
constexpr float HALF_SCREEN_SIZE_Y_WORLD(HALF_SCREEN_SIZE_Y / (float)PIXELS_PER_UNIT);


static std::unordered_map<std::string, std::unordered_map<std::string, AnimationData>>
ANIMATION_DATA(
{
  {"kadijah",
    {
      {"body-idle-front", {0 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"body-idle-back", {0 * PIXELS_PER_UNIT, 1 * PIXELS_PER_UNIT, 1}},
      {"body-idle-left", {0 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, 1}},
      {"body-idle-right", {0 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, 1}},
      {"body-walk-front", {0 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 4}},
      {"body-walk-back", {0 * PIXELS_PER_UNIT, 1 * PIXELS_PER_UNIT, 4}},
      {"body-walk-left", {0 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, 4}},
      {"body-walk-right", {0 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, 4}},
      {"arm-idle-nequip-front", {4 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-lequip-front", {5 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-requip-front", {6 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-bequip-front", {7 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-nequip-back", {4 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-lequip-back", {6 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-requip-back", {5 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-bequip-back", {7 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-nequip-left", {4 * PIXELS_PER_UNIT, 1 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-lequip-left", {5 * PIXELS_PER_UNIT, 1 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-requip-left", {6 * PIXELS_PER_UNIT, 1 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-bequip-left", {7 * PIXELS_PER_UNIT, 1 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-nequip-right", {4 * PIXELS_PER_UNIT, 1 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-lequip-right", {6 * PIXELS_PER_UNIT, 1 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-requip-right", {5 * PIXELS_PER_UNIT, 1 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-bequip-right", {7 * PIXELS_PER_UNIT, 1 * PIXELS_PER_UNIT, 1}},
      {"arm-walk-nequip-front", {4 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-walk-lequip-front", {5 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-walk-requip-front", {6 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-walk-bequip-front", {7 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-walk-nequip-back", {4 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-walk-lequip-back", {6 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-walk-requip-back", {5 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-walk-bequip-back", {7 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-walk-nequip-left", {4 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, 4}},
      {"arm-walk-lequip-left", {4 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, 4}},
      {"arm-walk-requip-left", {4 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, 4}},
      {"arm-walk-bequip-left", {4 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, 4}},
      {"arm-walk-nequip-right", {4 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, 4}},
      {"arm-walk-lequip-right", {4 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, 4}},
      {"arm-walk-requip-right", {4 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, 4}},
      {"arm-walk-bequip-right", {4 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, 4}},
    }
  },
  {"kathryn",
    {
      {"body-idle-front", {0 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"body-idle-back", {0 * PIXELS_PER_UNIT, 1 * PIXELS_PER_UNIT, 1}},
      {"body-idle-left", {0 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, 1}},
      {"body-idle-right", {0 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, 1}},
      {"body-walk-front", {0 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 4}},
      {"body-walk-back", {0 * PIXELS_PER_UNIT, 1 * PIXELS_PER_UNIT, 4}},
      {"body-walk-left", {0 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, 4}},
      {"body-walk-right", {0 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, 4}},
      {"arm-idle-nequip-front", {4 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-lequip-front", {5 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-requip-front", {6 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-bequip-front", {7 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-nequip-back", {4 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-lequip-back", {6 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-requip-back", {5 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-bequip-back", {7 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-nequip-left", {4 * PIXELS_PER_UNIT, 1 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-lequip-left", {5 * PIXELS_PER_UNIT, 1 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-requip-left", {6 * PIXELS_PER_UNIT, 1 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-bequip-left", {7 * PIXELS_PER_UNIT, 1 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-nequip-right", {4 * PIXELS_PER_UNIT, 1 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-lequip-right", {6 * PIXELS_PER_UNIT, 1 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-requip-right", {5 * PIXELS_PER_UNIT, 1 * PIXELS_PER_UNIT, 1}},
      {"arm-idle-bequip-right", {7 * PIXELS_PER_UNIT, 1 * PIXELS_PER_UNIT, 1}},
      {"arm-walk-nequip-front", {4 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-walk-lequip-front", {5 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-walk-requip-front", {6 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-walk-bequip-front", {7 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-walk-nequip-back", {4 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-walk-lequip-back", {6 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-walk-requip-back", {5 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-walk-bequip-back", {7 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, 1}},
      {"arm-walk-nequip-left", {4 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, 4}},
      {"arm-walk-lequip-left", {4 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, 4}},
      {"arm-walk-requip-left", {4 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, 4}},
      {"arm-walk-bequip-left", {4 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, 4}},
      {"arm-walk-nequip-right", {4 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, 4}},
      {"arm-walk-lequip-right", {4 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, 4}},
      {"arm-walk-requip-right", {4 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, 4}},
      {"arm-walk-bequip-right", {4 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, 4}},
    }
  },
});

}

#endif /* RENDERCONSTANTS_H */
