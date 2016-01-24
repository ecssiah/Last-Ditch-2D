#include "PhysicsSystem.h"

#include <iostream>

using namespace ld;
using namespace std;

PhysicsSystem::PhysicsSystem(EntitySystem& entity_system_)
  : entity_system(entity_system_)
{
  cout << "Physics system ready" << endl;
}


void PhysicsSystem::update(double dt)
{
  for (auto& entity : entity_system.get_dynamic_entities())
  {
    entity.pos[0] += dt * entity.vel.x();
    entity.pos[1] += dt * entity.vel.y();
  }
}
