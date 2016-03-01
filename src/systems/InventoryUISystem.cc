#include "InventoryUISystem.h"

#include "../constants/UIConstants.h"

using namespace ld;

InventoryUISystem::InventoryUISystem(
  SDL_Interface& _sdl_interface, Input& _input, EntitySystem& _entity_system
)
  : sdl_interface(_sdl_interface),
    input(_input),
    entity_system(_entity_system),
    active(false),
    menu_base(),
    inventory_list(),
    ui_elements(),
    scalable_elements()
{
  setup();
}


void InventoryUISystem::update()
{


}


void InventoryUISystem::render()
{
  sdl_interface.render_scalable_element(menu_base);

  for (auto& element : ui_elements)
    sdl_interface.render_element(element);

  for (auto& element : scalable_elements)
    sdl_interface.render_scalable_element(element);
}


void InventoryUISystem::setup()
{
  menu_base.type = "backdrop1";
  menu_base.texture = "ui1";
  menu_base.size = {SUB_MENU_BASE_SIZE_X, SUB_MENU_BASE_SIZE_Y};
  menu_base.pos =
    {(SCREEN_SIZE_X - SUB_MENU_BASE_SIZE_X) / 2,
     (SCREEN_SIZE_Y - SUB_MENU_BASE_SIZE_Y) / 2};

  UIElement title;
  title.text = "Inventory";
  title.text_texture = "inventory-title-text";
  title.size = {200, 30};
  title.pos =
    {menu_base.pos.x() + (SUB_MENU_BASE_SIZE_X - title.size.x()) / 2,
     menu_base.pos.y()};

  sdl_interface.create_texture_from_text(title.text, title.text_texture, "jura-medium-22");

  ui_elements.push_back(title);

  inventory_list.type = "list1";
  inventory_list.texture = "ui1";
}
