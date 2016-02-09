#include "CameraSystem.h"

#include <eigen3/Eigen/Geometry>
#include <iostream>

#include "../constants/MapConstants.h"
#include "../constants/RenderConstants.h"

using namespace ld;
using namespace Eigen;
using namespace std;

CameraSystem::CameraSystem()
  : pos(0, 0),
    target(nullptr)
{
  cout << "Camera system ready" << endl;
}


void CameraSystem::update()
{
  pos = target->pos + Vector2f(.5, .5);
}


Vector2f CameraSystem::to_world_coordinates(Vector2i screen_pos)
{
  Vector2f scaled_screen_pos(
    (float)screen_pos.x() / PIXELS_PER_UNIT,
    (float)screen_pos.y() / PIXELS_PER_UNIT);

  Vector2f world_pos(
    scaled_screen_pos.x() + pos.x() - SCREEN_SIZE_X / 2.f / PIXELS_PER_UNIT,
    scaled_screen_pos.y() + pos.y() - SCREEN_SIZE_Y / 2.f / PIXELS_PER_UNIT);

  return world_pos;
}
