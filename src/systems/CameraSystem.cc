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
  pos = users[0].pos + Vector2f(.5, .5);
}

}
