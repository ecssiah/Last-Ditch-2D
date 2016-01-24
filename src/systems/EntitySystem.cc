#include "EntitySystem.h"

#include <iostream>

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
  kadijah.pos = {10.3, 2.1};
  kadijah.floor = 0;
  kadijah.clip_rect.w = 48;
  kadijah.clip_rect.h = 48;
  kadijah.dest_rect.w = 48;
  kadijah.dest_rect.h = 48;

  dynamic_entities.push_back(kadijah);
  active_user = &kadijah;
}


void EntitySystem::update()
{
  Vector2f direction;

  if (input.up) direction[1] += 1;
  if (input.down) direction[1] -= 1;
  if (input.left) direction[0] -= 1;
  if (input.right) direction[0] += 1;

  direction.norm();

  active_user->vel = active_user->speed * direction;
}
