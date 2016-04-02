#include "CameraSystem.h"

#include <cassert>
#include <eigen3/Eigen/Geometry>
#include <iostream>

#include "../constants/MapConstants.h"
#include "../constants/RenderConstants.h"

using namespace ld;
using namespace Eigen;
using namespace std;

CameraSystem::CameraSystem(SDL_Interface& _sdl_interface)
  : pos(0, 0),
    target(nullptr),
    sdl_interface(_sdl_interface)
{
  cout << "CameraSystem ready" << endl;
}


void CameraSystem::update()
{
  pos = target->pos + Vector2f(.5, .5);

  sdl_interface.set_camera_pos(pos);
}
