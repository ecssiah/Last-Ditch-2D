#include "StatusUISystem.h"

#include "../../constants/UIConstants.h"

using namespace ld;

StatusUISystem::StatusUISystem(Input& _input, SDL_Interface& _sdl_interface)
  : input(_input),
    sdl_interface(_sdl_interface)
{
  setup();
}


void StatusUISystem::update()
{

}


void StatusUISystem::render()
{
  sdl_interface.render_window_element(base_window);
}


void StatusUISystem::setup()
{
  base_window.type = "window1";
  base_window.texture = "ui1";
  base_window.dest_rect.x = (SCREEN_SIZE_X - BASE_WINDOW_SIZE_X) / 2;
  base_window.dest_rect.y = (SCREEN_SIZE_Y - BASE_WINDOW_SIZE_Y) / 2;
  base_window.dest_rect.w = BASE_WINDOW_SIZE_X;
  base_window.dest_rect.h = BASE_WINDOW_SIZE_Y;

  sdl_interface.generate_window_element(base_window);
}
