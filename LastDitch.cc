#include "LastDitch.h"

#include <chrono>
#include <iostream>

using namespace ld;
using namespace std;

LastDitch::LastDitch()
  : sdl_interface(),
    input(),
    rng(SEED > 0 ? SEED : chrono::high_resolution_clock::now().time_since_epoch().count()),
    time_system(input),
    input_system(input),
    camera_system(),
    map_system(),
    entity_system(rng, input, camera_system, map_system),
    physics_system(sdl_interface.renderer, map_system, entity_system),
    ui_system(sdl_interface, input, time_system, entity_system),
    render_system(
      sdl_interface, map_system, entity_system, camera_system,
      ui_system, physics_system)
{
  camera_system.set_target(entity_system.get_active_user());

  cout << endl << "Starting Last Ditch..." << endl << endl;

  for (auto dt(0.0); !input.exit; time_system.tick())
  {
    input_system.update();
    entity_system.update();
    map_system.update();
    physics_system.update(dt);
    camera_system.update();
    ui_system.update();
    render_system.update(dt);
    dt = time_system.update();

    if (input.activate)
    {
      input.activate = false;
      cout << "unused activation" << endl;
    }
  }
}


int main()
{
  LastDitch app;

  return 0;
}
