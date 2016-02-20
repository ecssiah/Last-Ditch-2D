#ifndef RENDERCONSTANTS_H
#define RENDERCONSTANTS_H

#include <eigen3/Eigen/Geometry>
#include <map>
#include <string>

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

static std::map<std::string, std::string> TYPE_TO_TEXTURE(
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

static std::map<std::string, AnimationData> ANIMATION_DATA(
{
  {"kadijah-idle-forward", AnimationData(0, 0, 1)},
  {"kadijah-idle-back", AnimationData(1, 0, 1)},
  {"kadijah-idle-left", AnimationData(2, 0, 1)},
  {"kadijah-idle-right", AnimationData(2, 0, 1)},
  {"kadijah-walk-forward", AnimationData(0, 1, 2)},
  {"kadijah-walk-back", AnimationData(0, 2, 2)},
  {"kadijah-walk-left", AnimationData(0, 3, 4)},
  {"kadijah-walk-right", AnimationData(0, 3, 4)},
});

}

#endif /* RENDERCONSTANTS_H */
