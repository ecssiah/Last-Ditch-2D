#include "EntitySystem.h"

#include <eigen3/Eigen/Geometry>
#include <iostream>

#include "../constants/MapConstants.h"
#include "../constants/RenderConstants.h"

using namespace ld;
using namespace Eigen;
using namespace std;

EntitySystem::EntitySystem(Input& input_)
  : input(input_),
    active_user(nullptr),
    dynamic_entities()
{
  cout << "Entity system ready" << endl;

  DynamicEntity kadijah;
  kadijah.name = "Kadijah";
  kadijah.type = "kadijah";
  kadijah.pos = {4, 9};
  kadijah.floor = 0;
  kadijah.speed = 800;
  kadijah.clip_rect.w = TILE_SIZE;
  kadijah.clip_rect.h = TILE_SIZE;

  dynamic_entities.push_back(kadijah);
  active_user = &dynamic_entities.back();
}


void EntitySystem::update()
{
  Vector2f direction(0, 0);

  if (input.left) direction.x() -= 1;
  if (input.right) direction.x() += 1;
  if (input.up) direction.y() -= 1;
  if (input.down) direction.y() += 1;

  if (direction.squaredNorm() != 0)
  {
    direction.normalize();
    active_user->vel = active_user->speed * direction;
  }
  else
    active_user->vel = Vector2f::Zero();
}
