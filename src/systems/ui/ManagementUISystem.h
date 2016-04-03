#ifndef MANAGEMENTUISYSTEM_H
#define MANAGEMENTUISYSTEM_H

#include <vector>

#include "../../components/Input.h"
#include "../../components/ui/Window.h"
#include "../../SDL_Interface.h"

namespace ld
{

class ManagementUISystem
{
  void setup();

  Input& input;
  SDL_Interface& sdl_interface;

  bool active;

  Window base_window;

public:
  ManagementUISystem(Input& input, SDL_Interface& sdl_interface);

  void update();
  void render();

  const bool& is_active() const { return active; }
  void set_active(bool _active) { active = _active; }
};

}

#endif /* MANAGEMENTUISYSTEM_H */
