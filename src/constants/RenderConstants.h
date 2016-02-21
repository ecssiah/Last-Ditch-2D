#ifndef RENDERCONSTANTS_H
#define RENDERCONSTANTS_H

#include <eigen3/Eigen/Geometry>
#include <map>
#include <string>
#include <unordered_map>

namespace ld
{

constexpr float PIXELS_PER_UNIT(48);
constexpr int SCREEN_SIZE_X(800);
constexpr int SCREEN_SIZE_Y(600);
constexpr int HALF_SCREEN_SIZE_X(SCREEN_SIZE_X / 2);
constexpr int HALF_SCREEN_SIZE_Y(SCREEN_SIZE_Y / 2);
constexpr float HALF_SCREEN_SIZE_X_WORLD(HALF_SCREEN_SIZE_X / (float)PIXELS_PER_UNIT);
constexpr float HALF_SCREEN_SIZE_Y_WORLD(HALF_SCREEN_SIZE_Y / (float)PIXELS_PER_UNIT);

struct AnimationData
{
  AnimationData()
    : x(0),
      y(0),
      frames(0)
  {}

  AnimationData(int _x, int _y, int _frames)
    : x(_x),
      y(_y),
      frames(_frames)
  {}

  int x, y;
  int frames;
};

static std::unordered_map<std::string, std::string> TYPE_TO_TEXTURE(
{
  {"kadijah", "kadijah"},
  {"chunk1", "chunk_floor1"},
  {"wall1", "tileset1"},
  {"door1", "tileset1"},
  {"floor1", "tileset1"},
  {"stairs_up1", "tileset1"},
  {"stairs_down1", "tileset1"},
  {"scrub1", "items1"},
  {"container1", "items1"},
});

static std::unordered_map<std::string, std::unordered_map<std::string, AnimationData>>
ANIMATION_DATA(
{
  {"kadijah",
    {
      {"body-idle-front", {0, 0, 1}},
      {"body-idle-back", {0, 1, 1}},
      {"body-idle-left", {0, 2, 1}},
      {"body-idle-right", {0, 2, 1}},
      {"body-walk-front", {0, 0, 4}},
      {"body-walk-back", {0, 1, 4}},
      {"body-walk-left", {0, 2, 4}},
      {"body-walk-right", {0, 2, 4}},
      {"arm-idle-nequip-front", {4, 0, 1}},
      {"arm-idle-lequip-front", {5, 0, 1}},
      {"arm-idle-requip-front", {6, 0, 1}},
      {"arm-idle-bequip-front", {7, 0, 1}},
      {"arm-idle-nequip-back", {4, 0, 1}},
      {"arm-idle-lequip-back", {6, 0, 1}},
      {"arm-idle-requip-back", {5, 0, 1}},
      {"arm-idle-bequip-back", {7, 0, 1}},
      {"arm-idle-nequip-left", {4, 1, 1}},
      {"arm-idle-lequip-left", {5, 1, 1}},
      {"arm-idle-requip-left", {6, 1, 1}},
      {"arm-idle-bequip-left", {7, 1, 1}},
      {"arm-idle-nequip-right", {4, 1, 1}},
      {"arm-idle-lequip-right", {6, 1, 1}},
      {"arm-idle-requip-right", {5, 1, 1}},
      {"arm-idle-bequip-right", {7, 1, 1}},
      {"arm-walk-nequip-front", {4, 0, 1}},
      {"arm-walk-lequip-front", {5, 0, 1}},
      {"arm-walk-requip-front", {6, 0, 1}},
      {"arm-walk-bequip-front", {7, 0, 1}},
      {"arm-walk-nequip-back", {4, 0, 1}},
      {"arm-walk-lequip-back", {6, 0, 1}},
      {"arm-walk-requip-back", {5, 0, 1}},
      {"arm-walk-bequip-back", {7, 0, 1}},
      {"arm-walk-nequip-left", {4, 2, 4}},
      {"arm-walk-lequip-left", {4, 2, 4}},
      {"arm-walk-requip-left", {4, 2, 4}},
      {"arm-walk-bequip-left", {4, 2, 4}},
      {"arm-walk-nequip-right", {4, 2, 4}},
      {"arm-walk-lequip-right", {4, 2, 4}},
      {"arm-walk-requip-right", {4, 2, 4}},
      {"arm-walk-bequip-right", {4, 2, 4}},
    }
  },
  {"kathryn",
    {
      {"body-idle-front", {0, 0, 1}},
      {"body-idle-back", {0, 1, 1}},
      {"body-idle-left", {0, 2, 1}},
      {"body-idle-right", {0, 2, 1}},
      {"body-walk-front", {0, 0, 4}},
      {"body-walk-back", {0, 1, 4}},
      {"body-walk-left", {0, 2, 4}},
      {"body-walk-right", {0, 2, 4}},
      {"arm-idle-nequip-front", {4, 0, 1}},
      {"arm-idle-lequip-front", {5, 0, 1}},
      {"arm-idle-requip-front", {6, 0, 1}},
      {"arm-idle-bequip-front", {7, 0, 1}},
      {"arm-idle-nequip-back", {4, 0, 1}},
      {"arm-idle-lequip-back", {6, 0, 1}},
      {"arm-idle-requip-back", {5, 0, 1}},
      {"arm-idle-bequip-back", {7, 0, 1}},
      {"arm-idle-nequip-left", {4, 1, 1}},
      {"arm-idle-lequip-left", {5, 1, 1}},
      {"arm-idle-requip-left", {6, 1, 1}},
      {"arm-idle-bequip-left", {7, 1, 1}},
      {"arm-idle-nequip-right", {4, 1, 1}},
      {"arm-idle-lequip-right", {6, 1, 1}},
      {"arm-idle-requip-right", {5, 1, 1}},
      {"arm-idle-bequip-right", {7, 1, 1}},
      {"arm-walk-nequip-front", {4, 0, 1}},
      {"arm-walk-lequip-front", {5, 0, 1}},
      {"arm-walk-requip-front", {6, 0, 1}},
      {"arm-walk-bequip-front", {7, 0, 1}},
      {"arm-walk-nequip-back", {4, 0, 1}},
      {"arm-walk-lequip-back", {6, 0, 1}},
      {"arm-walk-requip-back", {5, 0, 1}},
      {"arm-walk-bequip-back", {7, 0, 1}},
      {"arm-walk-nequip-left", {4, 2, 4}},
      {"arm-walk-lequip-left", {4, 2, 4}},
      {"arm-walk-requip-left", {4, 2, 4}},
      {"arm-walk-bequip-left", {4, 2, 4}},
      {"arm-walk-nequip-right", {4, 2, 4}},
      {"arm-walk-lequip-right", {4, 2, 4}},
      {"arm-walk-requip-right", {4, 2, 4}},
      {"arm-walk-bequip-right", {4, 2, 4}},
    }
  },
});

}

#endif /* RENDERCONSTANTS_H */
