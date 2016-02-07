#include "LastDitch.h"

#include <chrono>
#include <iostream>

using namespace ld;
using namespace std;

LastDitch::LastDitch()
  : sdl_interface(),
    input(),
    rng(SEED > 0 ? SEED : chrono::high_resolution_clock::now().time_since_epoch().count()),
    time_system(),
    input_system(input),
    map_system(),
    entity_system(rng, input, map_system),
    physics_system(sdl_interface.renderer, map_system, entity_system),
    camera_system(entity_system),
    interface_system(sdl_interface, time_system, entity_system),
    render_system(
      sdl_interface, map_system, entity_system, camera_system,
      interface_system, physics_system)
{
  cout << endl << "Starting Last Ditch..." << endl << endl;

  while (!input.exit)
  {
    auto dt = time_system.update();

    input_system.update();
    entity_system.update();
    map_system.update();
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
