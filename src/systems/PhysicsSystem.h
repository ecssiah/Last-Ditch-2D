#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "EntitySystem.h"
#include "MapSystem.h"

namespace ld
{

class PhysicsSystem
{
  EntitySystem& entity_system;

public:
  PhysicsSystem(EntitySystem& entity_system);

  void update(double dt);
};

}

#endif /* PHYSICSSYSTEM_H */
