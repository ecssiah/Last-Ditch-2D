#ifndef MANAGEMENTUISYSTEM_H
#define MANAGEMENTUISYSTEM_H

#include <vector>

#include "../components/Input.h"
#include "../components/UIElement.h"
#include "../components/ScalableElement.h"
#include "../SDL_Interface.h"

namespace ld
{

class ManagementUISystem
{
  void setup();

  SDL_Interface& sdl_interface;
  Input& input;

  bool active;

  ScalableElement menu_base;

  std::vector<UIElement> ui_elements;
  std::vector<ScalableElement> scalable_elements;

public:
  ManagementUISystem(SDL_Interface& sdl_interface, Input& input);

  const bool& get_active() const { return active; }
  void set_active(bool _active) { active = _active; }

  void update();
  void render();
};

}

#endif /* MANAGEMENTUISYSTEM_H */
