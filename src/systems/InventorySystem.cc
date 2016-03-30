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
