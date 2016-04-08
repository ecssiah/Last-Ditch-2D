#include "LastDitch.h"

#include <chrono>

using namespace std;

namespace ld
{

LastDitch::LastDitch()
  : rng(SEED > 0 ? SEED : chrono::high_resolution_clock::now().time_since_epoch().count()),
    configuration_system(),
    time_system(input),
    input_system(input),
    map_system(),
    camera_system(sdl_interface, users),
    entity_system(rng, input, users, camera_system, map_system),
    inventory_system(entity_system),
    physics_system(users, map_system, entity_system),
    ui_system(sdl_interface, input, time_system, entity_system, inventory_system),
    render_system(
      sdl_interface, map_system, entity_system, camera_system,
      ui_system, physics_system)
{
  for (auto dt(0.0); !input.exit; time_system.tick())
  {
    input_system.update();
    entity_system.update();
    inventory_system.update();
    map_system.update();
    physics_system.update(dt);
    camera_system.update();
    ui_system.update();
    render_system.update(dt);

    dt = time_system.update();
  }
}

}

int main()
{
  ld::LastDitch app;

  return 0;
}
