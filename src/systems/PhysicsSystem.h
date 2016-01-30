#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <eigen3/Eigen/Geometry>

#include "MapSystem.h"
#include "EntitySystem.h"

namespace ld
{

constexpr int ITERATIONS = 1;

class PhysicsSystem
{
  void scan_collisions(const Eigen::Vector2f& step, DynamicEntity& entity);
  float swept_AABB(DynamicEntity& entity, int x, int y, Eigen::Vector2f& normal);

  MapSystem& map_system;
  EntitySystem& entity_system;

public:
  PhysicsSystem(MapSystem& map_system, EntitySystem& entity_system);

  void update(double dt);
};

}

#endif /* PHYSICSSYSTEM_H */
