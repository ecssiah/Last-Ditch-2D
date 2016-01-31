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

    scan_collisions(step, entity);
  }
}


void PhysicsSystem::scan_collisions(const Vector2f& step, DynamicEntity& entity)
{
  int px, py;

  px = (int)std::floor(entity.pos.x());
  py = (int)std::floor(entity.pos.y());

  for (auto x = px - 1; x <= px + 1; ++x)
  {
    for (auto y = py - 1; y <= py + 1; ++y)
    {
      bool collision = false;

      if (map_system.get_tile(x, y, entity.floor).solid)
      {
	float u0, u1;
	Vector2f Ea(entity.size, entity.size);
	Vector2f Eb(1, 1);

	Vector2f A0(entity.pos.x() + .5, entity.pos.y() + .5);
	Vector2f A1(entity.pos.x() + step.x() + .5, entity.pos.y() + step.y() + .5);
	Vector2f B0(x + .5, y + .5);
	Vector2f B1(x + .5, y + .5);

	if (aabb_sweep(Ea, A0, A1, Eb, B0, B1, u0, u1))
	{
	  cout << u0 << " " << u1 << endl;
	  collision = true;
	}
      }

      if (!collision)
	entity.pos += step;
    }
  }
}


const bool PhysicsSystem::aabb_sweep(
  Vector2f& Ea, Vector2f& A0, Vector2f& A1,
  Vector2f& Eb, Vector2f& B0, Vector2f& B1,
  float& u0, float& u1)
{
  AABB A(A0, Ea);
  AABB B(B0, Eb);

  Vector2f va(A1 - A0);
  Vector2f vb(B1 - B0);
  Vector2f v(vb - va);

  Vector2f u_0(0, 0);
  Vector2f u_1(1, 1);

  if (A.overlaps(B))
  {
    u0 = u1 = 0;
    return true;
  }

  for (auto i = 0; i < 2; ++i)
  {
    if (A.max(i) < B.min(i) && v[i] < 0)
      u_0[i] = (A.max(i) - B.min(i)) / v[i];
    else if (B.max(i) < A.min(i) && v[i] > 0)
      u_0[i] = (A.min(i) - B.max(i)) / v[i];

    if (B.max(i) > A.min(i) && v[i] < 0)
      u_1[i] = (A.min(i) - B.max(i)) / v[i];
    else if (A.max(i) > B.min(i) && v[i] > 0)
      u_1[i] = (A.max(i) - B.min(i)) / v[i];
  }

  u0 = std::max(u_0.x(), u_0.y());
  u1 = std::min(u_1.x(), u_1.y());

  return u0 <= u1;
}
