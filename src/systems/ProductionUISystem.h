#ifndef PRODUCTIONUISYSTEM_H
#define PRODUCTIONUISYSTEM_H

#include <vector>

#include "../components/Input.h"
#include "../components/ui/Window.h"
#include "../SDL_Interface.h"

namespace ld
{

class ProductionUISystem
{
  void setup();

  Input& input;
  SDL_Interface& sdl_interface;

  bool active;

  Window base_window;

public:
  ProductionUISystem(Input& input, SDL_Interface& sdl_interface);

  void update();
  void render();

  const bool& is_active() const { return active; }
  void set_active(bool _active) { active = _active; }

};

}

#endif /* PRODUCTIONUISYSTEM_H */
