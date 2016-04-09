#include "ManagementUISystem.h"

#include "../../constants/UIConstants.h"

namespace ld
{

ManagementUISystem::ManagementUISystem(
  Input& _input, SDL_Interface& _sdl_interface
)
  : input(_input),
    sdl_interface(_sdl_interface),
    active(false)
{
  setup();
}


void ManagementUISystem::update()
{

}


void ManagementUISystem::render()
{
  sdl_interface.render_element(base_window);
}


void ManagementUISystem::setup()
{
  base_window.type = "window1";
  base_window.source_texture = "ui1";
  base_window.batch_texture = "ui1-batch";

  base_window.clip_rect = sdl_interface.batch_element(base_window);
  base_window.dest_rect.x = (SCREEN_SIZE_X - BASE_WINDOW_SIZE_X) / 2;
  base_window.dest_rect.y = (SCREEN_SIZE_Y - BASE_WINDOW_SIZE_Y) / 2;
  base_window.dest_rect.w = BASE_WINDOW_SIZE_X;
  base_window.dest_rect.h = BASE_WINDOW_SIZE_Y;
}

}
