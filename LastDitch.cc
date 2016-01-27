#include "LastDitch.h"

#include <iostream>

using namespace ld;
using namespace std;

LastDitch::LastDitch()
  : sdl_interface(),
    input(),
    time_system(),
    input_system(input),
    map_system(),
    entity_system(input),
    physics_system(map_system, entity_system),
    camera_system(entity_system),
    interface_system(sdl_interface),
    render_system(sdl_interface, map_system, entity_system, camera_system, interface_system)
{
  cout << endl << "Starting Last Ditch..." << endl << endl;

  while (!input.exit)
  {
    auto dt = time_system.update();

    input_system.update();
    entity_system.update();
    physics_system.update(dt);
    camera_system.update();
    interface_system.update();
    render_system.update();

    time_system.tick();
  }

  render_system.shutdown();
  sdl_interface.shutdown();
}


int main()
{
  LastDitch app;

  return 0;
}
