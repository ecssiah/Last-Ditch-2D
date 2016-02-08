#include "CameraSystem.h"

#include <eigen3/Eigen/Geometry>
#include <iostream>

#include "../constants/MapConstants.h"
#include "../constants/RenderConstants.h"

using namespace ld;
using namespace Eigen;
using namespace std;

CameraSystem::CameraSystem(EntitySystem& entity_system_)
  : entity_system(entity_system_),
    pos(0, 0),
    target(nullptr)
{
  for (auto& user : entity_system.get_users())
    if (user.name == "Kadijah") target = &user;

  cout << "Camera system ready" << endl;
}


void CameraSystem::update()
{
  pos = target->pos + Vector2f(.5, .5);
}
