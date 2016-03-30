#include "InventorySystem.h"

#include <iostream>

using namespace ld;
using namespace std;

InventorySystem::InventorySystem(EntitySystem& _entity_system)
  : entity_system(_entity_system)
{
  cout << "InventorySystem ready" << endl;
}


void InventorySystem::update()
{


}


Item* retrieve(std::string type, Inventory* inventory)
{
  for (auto item : inventory->items)
  {

  }

  return nullptr;
}


void store(Item item, Inventory* inventory)
{

}
