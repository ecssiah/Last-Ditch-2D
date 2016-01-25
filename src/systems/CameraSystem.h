#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>

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

  Eigen::Vector2f get_pos() { return pos; }
};

}


#endif /* CAMERASYSTEM_H */
