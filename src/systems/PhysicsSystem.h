#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <eigen3/Eigen/Geometry>

#include "MapSystem.h"
#include "EntitySystem.h"

namespace ld
{

struct Rect
{
  Rect(float x_, float y_, float w_, float h_)
    : x(x_),
      y(y_),
      w(w_),
      h(h_)
  {}

  bool overlaps(Rect& rect)
  {
    return !(rect.x > x + w || rect.x + w < x || rect.y > y + h || rect.y + rect.h < y);
  }

  float x, y;
  float w, h;
};

constexpr int ITERATIONS = 1;

class PhysicsSystem
{
  bool scan_collisions(const Eigen::Vector2f& step, DynamicEntity& entity);
  const bool aabb_sweep(DynamicEntity& entity, int x, int y, float& u0, float& u1);

  MapSystem& map_system;
  EntitySystem& entity_system;

public:
  PhysicsSystem(MapSystem& map_system, EntitySystem& entity_system);

  void update(double dt);
};

}

#endif /* PHYSICSSYSTEM_H */
