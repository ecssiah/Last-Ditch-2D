#ifndef INVENTORYSYSTEM_H
#define INVENTORYSYSTEM_H

#include "EntitySystem.h"

namespace ld
{

class InventorySystem
{
  EntitySystem& entity_system;

public:
  InventorySystem(EntitySystem& entity_system);

  void update();
};

}


#endif /* INVENTORYSYSTEM_H */
