#include "CameraSystem.h"

#include <iostream>


using namespace ld;
using namespace std;

CameraSystem::CameraSystem(EntitySystem& entity_system_)
  : entity_system(entity_system_),
    main_view(),
    target(nullptr)
{
  main_view.x = 0;
  main_view.y = 0;
  main_view.w = 800;
  main_view.h = 600;

  for (auto& entity : entity_system.get_dynamic_entities())
    if (entity.name == "Kadijah") target = &entity;

  cout << "Camera system ready" << endl;
}


void CameraSystem::update()
{
  main_view.x = target->pos.x();
  main_view.y = target->pos.y();
}
