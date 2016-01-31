#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <eigen3/Eigen/Geometry>

#include "MapSystem.h"
#include "EntitySystem.h"

namespace ld
{

struct AABB
{
  AABB(Eigen::Vector2f P_, Eigen::Vector2f E_)
    : P(P_),
      E(E_)
  {}

  const bool overlaps(const AABB& b)
  {
    const Eigen::Vector2f T(b.P - P);

    return
      fabs(T.x()) <= (E.x() + b.E.x()) &&
      fabs(T.y()) <= (E.y() + b.E.y());
  }

  const float min(long i) const
  {
    return (P[i] - E[i]);
  }

  const float max(long i) const
  {
    return (P[i] + E[i]);
  }

  Eigen::Vector2f P;
  Eigen::Vector2f E;
};

constexpr int ITERATIONS = 1;

class PhysicsSystem
{
  void scan_collisions(const Eigen::Vector2f& step, DynamicEntity& entity);
  const bool aabb_sweep(
    Eigen::Vector2f& Ea, Eigen::Vector2f& A0, Eigen::Vector2f& A1,
    Eigen::Vector2f& Eb, Eigen::Vector2f& B0, Eigen::Vector2f& B1,
    float& u0, float& u1);

  MapSystem& map_system;
  EntitySystem& entity_system;

public:
  PhysicsSystem(MapSystem& map_system, EntitySystem& entity_system);

  void update(double dt);
};

}

#endif /* PHYSICSSYSTEM_H */
