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
    auto step = dt * entity.vel / ITERATIONS;

    for (auto i = 0; i < ITERATIONS; ++i)
    {
      entity.pos += step;

      scan_collisions(entity);
    }
  }
}


void PhysicsSystem::scan_collisions(DynamicEntity& entity)
{
  int px, py;

  px = (int)std::floor(entity.pos.x());
  py = (int)std::floor(entity.pos.y());

  if (entity.vel.x() > 0)
  {
    for (auto y = py - 1; y <= py + 1; ++y)
    {
      if ((px + 1) < 0 || (px + 1) >= MAP_SIZE_X || y < 0 || y >= MAP_SIZE_Y)
	continue;

      if (map_system.get_tile((px + 1), y, entity.floor).solid)
	resolve_collision(entity, (px + 1), y);
    }
  }
  else if (entity.vel.x() < 0)
  {
    for (auto y = py - 1; y <= py + 1; ++y)
    {
      if ((px - 1) < 0 || (px - 1) >= MAP_SIZE_X || y < 0 || y >= MAP_SIZE_Y)
	continue;

      if (map_system.get_tile((px - 1), y, entity.floor).solid)
	resolve_collision(entity, (px - 1), y);
    }
  }

  px = (int)std::floor(entity.pos.x());
  py = (int)std::floor(entity.pos.y());

  if (entity.vel.y() > 0)
  {
    for (auto x = px - 1; x <= px + 1; ++x)
    {
      if (x < 0 || x >= MAP_SIZE_X || (py + 1) < 0 || (py + 1) >= MAP_SIZE_Y)
	continue;

      if (map_system.get_tile(x, (py + 1), entity.floor).solid)
	resolve_collision(entity, x, (py + 1));
    }
  }
  else if (entity.vel.y() < 0)
  {
    for (auto x = px - 1; x <= px + 1; ++x)
    {
      if (x < 0 || x >= MAP_SIZE_X || (py - 1) < 0 || (py - 1) >= MAP_SIZE_Y)
	continue;

      if (map_system.get_tile(x, (py - 1), entity.floor).solid)
	resolve_collision(entity, x, (py - 1));
    }
  }
}


void PhysicsSystem::resolve_collision(DynamicEntity& entity, int x, int y)
{
  Vector2f tile_pos(x, y);
  Vector2f nearest(entity.pos);
  Vector2f min(x, y), max(x + 1, y + 1);

  if (nearest.x() < min.x()) nearest.x() = min.x();
  else if (nearest.x() > max.x()) nearest.x() = max.x();

  if (nearest.y() < min.y()) nearest.y() = min.y();
  else if (nearest.y() > max.y()) nearest.y() = max.y();

  Vector2f ray(entity.pos - nearest);
  auto length = ray.norm();
  auto depth = entity.size - length;

  if (length != 0 && depth > 0)
  {
    ray.normalize();
    entity.pos += depth * ray;
  }
}
