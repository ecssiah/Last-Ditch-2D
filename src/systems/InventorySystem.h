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

  Item* retrieve(std::string type, Inventory* inventory);
  void store(Item item, Inventory* inventory);
};

}


#endif /* INVENTORYSYSTEM_H */
