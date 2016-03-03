#ifndef PRODUCTIONUISYSTEM_H
#define PRODUCTIONUISYSTEM_H

#include <vector>

#include "../components/Input.h"
#include "../components/UIElement.h"
#include "../components/ScalableElement.h"
#include "../SDL_Interface.h"

namespace ld
{

class ProductionUISystem
{
  void setup();

  SDL_Interface& sdl_interface;
  Input& input;

  bool active;

  ScalableElement menu_base;

  std::vector<UIElement> ui_elements;
  std::vector<ScalableElement> scalable_elements;

public:
  ProductionUISystem(SDL_Interface& sdl_interface, Input& input);

  void update();
  void render();

  const bool& is_active() const { return active; }
  void set_active(bool _active) { active = _active; }

};

}

#endif /* PRODUCTIONUISYSTEM_H */