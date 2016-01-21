#ifndef LASTDITCH_H
#define LASTDITCH_H

#include <chrono>
#include <SDL2/SDL.h>

#include "src/SDL_Interface.h"
#include "src/components/Input.h"
#include "src/systems/InputSystem.h"
#include "src/systems/MapSystem.h"
#include "src/systems/EntitySystem.h"
#include "src/systems/PhysicsSystem.h"
#include "src/systems/CameraSystem.h"
#include "src/systems/RenderSystem.h"

namespace ld
{

class LastDitch
{
  SDL_Interface sdl_interface;

  Input input;

  InputSystem input_system;
  MapSystem map_system;
  EntitySystem entity_system;
  PhysicsSystem physics_system;
  CameraSystem camera_system;
  RenderSystem render_system;

  std::chrono::steady_clock::time_point start;
  std::chrono::steady_clock::time_point end;

public:
  LastDitch();
};

}

#endif /* LASTDITCH_H */
