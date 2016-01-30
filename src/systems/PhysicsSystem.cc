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
    Vector2f step = dt * entity.vel / ITERATIONS;

    if (step.norm() != 0)
      for (auto i = 0; i < ITERATIONS; ++i)
	scan_collisions(step, entity);
  }
}


void PhysicsSystem::scan_collisions(const Vector2f& step, DynamicEntity& entity)
{
  int px, py;

  px = (int)std::floor(entity.pos.x());
  py = (int)std::floor(entity.pos.y());

  if (entity.vel.x() > 0)
  {
    for (auto y = py; y <= py + 1; ++y)
    {
      if (px + 1 < 0 || px + 1 >= MAP_SIZE_X || y < 0 || y >= MAP_SIZE_Y)
	continue;

      if (map_system.get_tile(px + 1, y, entity.floor).solid)
      {
	Vector2f normal;
	float collision_time = swept_AABB(entity, px + 1, y, normal);

	entity.pos += collision_time * entity.vel;

	float remaining_time = 1.f - collision_time;
      }
    }
  }
  else
  {
    for (auto y = py; y <= py + 1; ++y)
    {
      if (px < 0 || px >= MAP_SIZE_X || y < 0 || y >= MAP_SIZE_Y)
	continue;

      if (map_system.get_tile(px, y, entity.floor).solid)
      {}
    }
  }

  px = (int)std::floor(entity.pos.x());
  py = (int)std::floor(entity.pos.y());

  if (entity.vel.y() > 0)
  {
    for (auto x = px; x <= px + 1; ++x)
    {
      if (x < 0 || x >= MAP_SIZE_X || py + 1 < 0 || py + 1 >= MAP_SIZE_Y)
	continue;

      if (map_system.get_tile(x, py + 1, entity.floor).solid)
      {}
    }
  }
  else
  {
    for (auto x = px; x <= px + 1; ++x)
    {
      if (x < 0 || x >= MAP_SIZE_X || py < 0 || py >= MAP_SIZE_Y)
	continue;

      if (map_system.get_tile(x, py, entity.floor).solid)
      {}
    }
  }
}


float PhysicsSystem::swept_AABB(DynamicEntity& entity, int x, int y, Eigen::Vector2f& normal)
{
  float inv_x_entry, inv_y_entry;
  float inv_x_exit, inv_y_exit;

  if (entity.vel.x() > 0.f)
  {
    inv_x_entry = x - (entity.pos.x() + entity.size);
    inv_x_exit = (x + 1) - entity.pos.x();
  }
  else
  {
    inv_x_entry = (x + 1) - entity.pos.x();
    inv_x_exit = x - (entity.pos.x() + entity.size);
  }

  if (entity.vel.y() > 0.f)
  {
    inv_y_entry = y - (entity.pos.y() + entity.size);
    inv_y_exit = (y + 1) - entity.pos.y();
  }
  else
  {
    inv_y_entry = (y + 1) - entity.pos.y();
    inv_y_exit = y - (entity.pos.y() + entity.size);
  }

  float x_entry, y_entry;
  float x_exit, y_exit;

  if (entity.vel.x() == 0.f)
  {
    x_entry = -std::numeric_limits<float>::infinity();
    x_exit = std::numeric_limits<float>::infinity();
  }
  else
  {
    x_entry = inv_x_entry / entity.vel.x();
    x_exit = inv_x_exit / entity.vel.x();
  }

  if (entity.vel.y() == 0.f)
  {
    y_entry = -std::numeric_limits<float>::infinity();
    y_exit = std::numeric_limits<float>::infinity();
  }
  else
  {
    y_entry = inv_y_entry / entity.vel.y();
    y_exit = inv_y_exit / entity.vel.y();
  }

  float entry_time = std::max(x_entry, y_entry);
  float exit_time = std::min(x_exit, y_exit);

  bool exit_before_entry = entry_time > exit_time;
  bool x_out_of_range = x_entry < 0.f || x_entry > 1.f;
  bool y_out_of_range = y_entry < 0.f || y_entry > 1.f;

  if (exit_before_entry || x_out_of_range || y_out_of_range)
  {
    normal = Vector2f::Zero();
    return 1.f;
  }
  else
  {
    if (x_entry > y_entry)
    {
      if (inv_x_entry < 0.f)
	normal = {1.f, 0.f};
      else
	normal = {-1.f, 0.f};
    }
    else
    {
      if (inv_y_entry < 0.f)
	normal = {0.f, 1.f};
      else
	normal = {0.f, -1.f};
    }

    return entry_time;
  }
}
