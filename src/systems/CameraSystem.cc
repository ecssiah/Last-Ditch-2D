#include "CameraSystem.h"

#include <cassert>
#include <eigen3/Eigen/Geometry>
#include <iostream>

using namespace ld;
using namespace Eigen;
using namespace std;

CameraSystem::CameraSystem(SDL_Interface& _sdl_interface, vector<User>& _users)
  : sdl_interface(_sdl_interface),
    users(_users)
{
  cout << "CameraSystem ready" << endl;
}


void CameraSystem::update()
{
  pos = users[0].pos + Vector2f(.5, .5);
}
