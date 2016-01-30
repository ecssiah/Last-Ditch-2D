#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>

#include "MapSystem.h"
#include "EntitySystem.h"

namespace ld
{

constexpr int ITERATIONS = 1;

class PhysicsSystem
{
  bool scan_collisions(const Eigen::Vector2f& step, DynamicEntity& entity);
  float swept_AABB(DynamicEntity& entity, int x, int y, Eigen::Vector2f& normal);
  SDL_Rect get_broadphase_bounds(DynamicEntity& entity);
  bool AABB_intersect(SDL_Rect r1, SDL_Rect r2);

  MapSystem& map_system;
  EntitySystem& entity_system;

public:
  PhysicsSystem(MapSystem& map_system, EntitySystem& entity_system);

  void update(double dt);
};

}

#endif /* PHYSICSSYSTEM_H */
