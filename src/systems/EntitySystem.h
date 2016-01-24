#ifndef ENTITYSYSTEM_H
#define ENTITYSYSTEM_H

#include <vector>

#include "../components/DynamicEntity.h"
#include "../components/Input.h"

namespace ld
{

class EntitySystem
{
  Input& input;

  DynamicEntity* active_user;
  std::vector<DynamicEntity> dynamic_entities;

public:
  EntitySystem(Input& input);

  void update();

  std::vector<DynamicEntity>& get_dynamic_entities() { return dynamic_entities; }
};

}

#endif /* ENTITYSYSTEM_H */
