#include "InventorySystem.h"

#include <iostream>

using namespace std;

namespace ld
{

InventorySystem::InventorySystem(EntitySystem& _entity_system)
  : entity_system(_entity_system)
{
  printf("InventorySystem ready\n");
}


void InventorySystem::update()
{


}


Item* InventorySystem::retrieve(std::string type, Inventory* inventory)
{
  for (auto item : inventory->items)
  {

  }

  return nullptr;
}


void InventorySystem::store(Item item, Inventory* inventory)
{

}

}
