#include "CameraSystem.h"

#include <cassert>
#include <eigen3/Eigen/Geometry>
#include <iostream>

using namespace Eigen;
using namespace std;

namespace ld
{

CameraSystem::CameraSystem(SDL_Interface& _sdl_interface, vector<User>& _users)
  : sdl_interface(_sdl_interface),
    users(_users)
{
  printf("CameraSystem ready\n");
}


void CameraSystem::update()
{
  Vector2f offset(.5f - HALF_SCREEN_SIZE_X_WORLD, .5f - HALF_SCREEN_SIZE_Y_WORLD);

  pos = users[0].pos + offset;

  sdl_interface.set_camera_position(pos);
}

}
