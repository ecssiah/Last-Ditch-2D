#include "LastDitch.h"

#include <iostream>
#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>

using namespace ld;
using namespace std;

LastDitch::LastDitch()
  : sdl_interface(),
    input(),
    input_system(input),
    map_system(),
    entity_system(),
    physics_system(),
    camera_system(),
    render_system(),
    start(chrono::steady_clock::now()),
    end(chrono::steady_clock::now())
{
  while (!input.exit)
  {
    end = chrono::steady_clock::now();
    auto microseconds = chrono::duration_cast<chrono::microseconds>(end - start).count();
    auto dt = microseconds / 100.0;

    cout << dt << endl;

    input_system.update();

    start = chrono::steady_clock::now();
  }

  sdl_interface.shutdown();
}


int main()
{
  LastDitch app;

  return 0;
}
