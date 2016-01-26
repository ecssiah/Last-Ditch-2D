#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "MapSystem.h"
#include "EntitySystem.h"

namespace ld
{

class PhysicsSystem
{
  void scan_collisions(DynamicEntity& entity);
  void resolve_collision(DynamicEntity& entity, int x, int y);

  MapSystem& map_system;
  EntitySystem& entity_system;

public:
  PhysicsSystem(MapSystem& map_system, EntitySystem& entity_system);

  void update(double dt);
};

}

#endif /* PHYSICSSYSTEM_H */
