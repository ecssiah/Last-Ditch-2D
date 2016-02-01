#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <Box2D/Box2D.h>
#include <eigen3/Eigen/Geometry>

#include "MapSystem.h"
#include "EntitySystem.h"

namespace ld
{

constexpr float32 B2D_TIMESTEP = 1 / 30.f;
constexpr int32 B2D_VELOCITY_ITERATIONS = 1;
constexpr int32 B2D_POSITION_ITERATIONS = 1;

class PhysicsSystem
{
  void setup_tile_bodies();
  void setup_entity_bodies();

  MapSystem& map_system;
  EntitySystem& entity_system;

  b2World* world;

  std::vector<b2Body*> dynamic_bodies;
  std::vector<b2Body*> tile_bodies;

public:
  PhysicsSystem(MapSystem& map_system, EntitySystem& entity_system);
  ~PhysicsSystem();

  void update(double dt);
};

}

#endif /* PHYSICSSYSTEM_H */
