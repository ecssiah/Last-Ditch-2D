#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include <SDL2/SDL.h>

#include "../components/DynamicEntity.h"
#include "EntitySystem.h"

namespace ld
{

class CameraSystem
{
  EntitySystem& entity_system;

  SDL_Rect main_view;

  DynamicEntity* target;

public:
  CameraSystem(EntitySystem& entity_system);

  void update();
};

}


#endif /* CAMERASYSTEM_H */
