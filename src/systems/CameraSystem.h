#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>

#include "../constants/MapConstants.h"
#include "../constants/RenderConstants.h"
#include "../components/DynamicEntity.h"
#include "EntitySystem.h"

namespace ld
{

class CameraSystem
{
  EntitySystem& entity_system;

  Eigen::Vector2f pos;

  DynamicEntity* target;

public:
  CameraSystem(EntitySystem& entity_system);

  void update();

  inline Eigen::Vector2f get_pos() { return pos; }
  inline Eigen::Vector2i get_pos_in_pixels();
};


Eigen::Vector2i CameraSystem::get_pos_in_pixels()
{
  Eigen::Vector2i pixel_pos(
    PIXELS_PER_UNIT * pos.x() + SCREEN_SIZE_X / 2,
    PIXELS_PER_UNIT * pos.y() + SCREEN_SIZE_Y / 2);

  return pixel_pos;
}

}


#endif /* CAMERASYSTEM_H */
