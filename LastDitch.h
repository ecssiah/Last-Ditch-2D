#ifndef LASTDITCH_H
#define LASTDITCH_H

#include <chrono>
#include <random>
#include <SDL2/SDL.h>

#include "src/SDL_Interface.h"
#include "src/components/Input.h"
#include "src/systems/ConfigurationSystem.h"
#include "src/systems/TimeSystem.h"
#include "src/systems/InputSystem.h"
#include "src/systems/MapSystem.h"
#include "src/systems/EntitySystem.h"
#include "src/systems/InventorySystem.h"
#include "src/systems/PhysicsSystem.h"
#include "src/systems/CameraSystem.h"
#include "src/systems/UISystem.h"
#include "src/systems/RenderSystem.h"

namespace ld
{

constexpr long SEED(1);

class LastDitch
{
  SDL_Interface sdl_interface;

  Input input;

  std::mt19937 rng;

  ConfigurationSystem configuration_system;
  TimeSystem time_system;
  InputSystem input_system;
  MapSystem map_system;
  EntitySystem entity_system;
  InventorySystem inventory_system;
  PhysicsSystem physics_system;
  CameraSystem camera_system;
  UISystem ui_system;
  RenderSystem render_system;

public:
  LastDitch();
};

}

#endif /* LASTDITCH_H */
