#include "StatusUISystem.h"

#include "../constants/UIConstants.h"

using namespace ld;

StatusUISystem::StatusUISystem(
  SDL_Interface& _sdl_interface, Input& _input
)
  : sdl_interface(_sdl_interface),
    input(_input),
    active(false),
    ui_elements(),
    scalable_elements()
{
  setup();
}


void StatusUISystem::update()
{

}


void StatusUISystem::render()
{
  sdl_interface.render_scalable_element(menu_base);

  for (auto& element : ui_elements)
    sdl_interface.render_element(element);

  for (auto& element : scalable_elements)
    sdl_interface.render_scalable_element(element);
}


void StatusUISystem::setup()
{
  menu_base.type = "backdrop1";
  menu_base.texture = "ui1";
  menu_base.size = {SUB_MENU_BASE_SIZE_X, SUB_MENU_BASE_SIZE_Y};
  menu_base.pos =
    {(SCREEN_SIZE_X - SUB_MENU_BASE_SIZE_X) / 2,
     (SCREEN_SIZE_Y - SUB_MENU_BASE_SIZE_Y) / 2};

  UIElement title;
  title.text = "Status";
  title.text_texture = "status-title-text";
  title.size = {200, 30};
  title.pos =
    {menu_base.pos.x() + (SUB_MENU_BASE_SIZE_X - title.size.x()) / 2,
     menu_base.pos.y()};

  sdl_interface.create_texture_from_text(title.text, title.text_texture, "jura-medium");

  ui_elements.push_back(title);
}