#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "EntitySystem.h"
#include "MapSystem.h"

namespace ld
{

class PhysicsSystem
{
public:
  PhysicsSystem();

  void update(double dt);
};

}

#endif /* PHYSICSSYSTEM_H */
