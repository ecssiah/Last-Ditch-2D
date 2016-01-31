#include "PhysicsSystem.h"

#include <eigen3/Eigen/Geometry>
#include <iostream>

using namespace ld;
using namespace Eigen;
using namespace std;

PhysicsSystem::PhysicsSystem(MapSystem& map_system_, EntitySystem& entity_system_)
  : map_system(map_system_),
    entity_system(entity_system_)
{
  cout << "Physics system ready" << endl;
}


void PhysicsSystem::update(double dt)
{
  for (auto& entity : entity_system.get_dynamic_entities())
  {
    auto step = dt * entity.vel;

    if (scan_collisions(step, entity) == false)
      entity.pos += step;
  }
}


bool PhysicsSystem::scan_collisions(const Vector2f& step, DynamicEntity& entity)
{
  int px, py;

  px = (int)std::floor(entity.pos.x());
  py = (int)std::floor(entity.pos.y());

  for (auto x = px - 1; x <= px + 1; ++x)
  {
    for (auto y = py - 1; y <= py + 1; ++y)
    {
      if (map_system.get_tile(x, y, entity.floor).solid)
      {
	float u0, u1;

	if (aabb_sweep(entity, x, y, u0, u1))
	{
	  cout << x << " " << y << endl;
	}
      }
    }
  }

  return false;
}


const bool PhysicsSystem::aabb_sweep(
  DynamicEntity& entity, int x, int y, float& u0, float& u1)
{
  Rect A(entity.pos.x(), entity.pos.y(), entity.size, entity.size);
  Rect B(x, y, 1, 1);

  Vector2f va(entity.pos - Vector2f(x, y));
  Vector2f uxy0(0, 0);
  Vector2f uxy1(1, 1);

  if (A.overlaps(B))
  {
    u0 = u1 = 0;
    return true;
  }
  else
  {
    if (A.x + A.w < B.x && -va.x() < 0)
      uxy0.x() = (A.x + A.w - B.x) / -va.x();
    else if (B.x + B.w < A.x && -va.x() > 0)
      uxy0.x() = (A.x - B.x + B.w) / -va.x();

    if (B.x + B.w > A.x && -va.x() < 0)
      uxy1.x() = (A.x - B.x + B.w) / -va.x();
    else if (A.x + A.w > B.x && -va.x() > 0)
      uxy1.x() = (A.x + A.w - B.x) / -va.x();

    if (A.y + A.w < B.y && -va.y() < 0)
      uxy0.y() = (A.y + A.w - B.y) / -va.y();
    else if (B.y + B.w < A.y && -va.y() > 0)
      uxy0.y() = (A.y - B.y + B.w) / -va.y();

    if (B.y + B.w > A.y && -va.y() < 0)
      uxy1.y() = (A.y - B.y + B.w) / -va.y();
    else if (A.y + A.w > B.y && -va.y() > 0)
      uxy1.y() = (A.y + A.w - B.y) / -va.y();
  }

  u0 = std::max(uxy0.x(), uxy0.y());
  u1 = std::min(uxy1.x(), uxy1.y());

  return u0 <= u1;
}
