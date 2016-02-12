#include "CameraSystem.h"

#include <cassert>
#include <eigen3/Eigen/Geometry>
#include <iostream>

#include "../constants/MapConstants.h"
#include "../constants/RenderConstants.h"

using namespace ld;
using namespace Eigen;
using namespace std;

CameraSystem::CameraSystem()
  : pos(0, 0),
    target(nullptr)
{
  cout << "Camera system ready" << endl;
}


void CameraSystem::update()
{
  pos = target->pos + Vector2f(.5, .5);
}
