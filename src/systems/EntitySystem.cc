#include "EntitySystem.h"

#include <iostream>

using namespace ld;
using namespace std;

EntitySystem::EntitySystem()
  : dynamic_entities()
{
  cout << "Entity system ready" << endl;

  DynamicEntity kadijah;
  kadijah.name = "Kadijah";
  kadijah.type = "kadijah";
  kadijah.pos = {2.3, 2.1};
  kadijah.floor = 0;
  kadijah.clip_rect.x = 0;
  kadijah.clip_rect.y = 0;
  kadijah.clip_rect.w = 48;
  kadijah.clip_rect.h = 48;

  dynamic_entities.push_back(kadijah);
}


void EntitySystem::update()
{
}
