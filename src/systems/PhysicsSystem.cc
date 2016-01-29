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
    entity.pos += dt * entity.vel;

    scan_collisions(entity);
  }
}


void PhysicsSystem::scan_collisions(DynamicEntity& entity)
{
  auto px = (int)std::floor(entity.pos.x());
  auto py = (int)std::floor(entity.pos.y());

  for (auto x = px - 1; x <= px + 1; ++x)
  {
    for (auto y = py - 1; y <= py + 1; ++y)
    {
      if (x < 0 || x >= MAP_SIZE_X || y < 0 || y >= MAP_SIZE_Y)
	continue;

      if (map_system.get_tile(x, y, entity.floor).solid)
	resolve_collision(entity, x, y);
    }
  }
}


void PhysicsSystem::resolve_collision(DynamicEntity& entity, int x, int y)
{
  Vector2f tile_pos(x + .5, y + .5);
  Vector2f entity_pos(entity.pos.x() + .5, entity.pos.y() + .5);
  Vector2f min(x - .5, y - .5);
  Vector2f max(x + .5, y + .5);
  Vector2f nearest(entity_pos);

  if (nearest.x() < min.x()) nearest.x() = min.x();
  else if (nearest.x() > max.x()) nearest.x() = max.x();

  if (nearest.y() < min.y()) nearest.y() = min.y();
  else if (nearest.y() > max.y()) nearest.y() = max.y();

  Vector2f normal(entity_pos - nearest);
  auto dist = normal.norm();
  auto depth = entity.size - dist;

  if (depth > 0)
  {
    cout << "Player:" << entity.pos.x() << " " << entity.pos.y() << endl;
    cout << "Collision:" << x << " " << y << endl;

    if (dist != 0)
      normal.normalize();

    entity.pos += depth * normal;

    cout << "Player after:" << entity.pos.x() << " " << entity.pos.y() << endl;
  }
}
