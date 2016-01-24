#ifndef ENTITYSYSTEM_H
#define ENTITYSYSTEM_H

#include <vector>

#include "../components/DynamicEntity.h"

namespace ld
{

class EntitySystem
{
  std::vector<DynamicEntity> dynamic_entities;

public:
  EntitySystem();

  void update();

  const std::vector<DynamicEntity>& get_dynamic_entities() { return dynamic_entities; }
};

}

#endif /* ENTITYSYSTEM_H */
