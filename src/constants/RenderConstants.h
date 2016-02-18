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

static std::map<std::string, Eigen::Vector3i> ANIMATION_COORDS(
{
  {"kadijah-idle-forward", {1, 0, 0}},
  {"kadijah-idle-back", {1, 1, 0}},
  {"kadijah-idle-side", {1, 2, 0}},
  {"kadijah-walk-forward", {2, 0, 1}},
  {"kadijah-walk-back", {2, 0, 2}},
  {"kadijah-walk-side", {2, 0, 3}},
});

}

#endif /* RENDERCONSTANTS_H */
