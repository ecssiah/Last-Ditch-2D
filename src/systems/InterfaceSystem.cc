#include "InterfaceSystem.h"

#include <iomanip>
#include <sstream>

#include "../constants/InterfaceConstants.h"

using namespace ld;
using namespace Eigen;
using namespace std;

InterfaceSystem::InterfaceSystem(
  SDL_Interface& _sdl_interface,
  Input& _input,
  TimeSystem& _time_system,
  CameraSystem& _camera_system,
  EntitySystem& _entity_system
)
  : sdl_interface(_sdl_interface),
    input(_input),
    time_system(_time_system),
    camera_system(_camera_system),
    entity_system(_entity_system),
    main_menu_active(),
    inventory_menu_active(),
    equipment_menu_active(),
    production_menu_active(),
    status_menu_active(),
    active_user(_entity_system.get_active_user()),
    fonts(),
    textures(),
    base_ui_elements(),
    base_scalable_elements(),
    date_and_time(nullptr),
    main_ui_elements(),
    main_scalable_elements()
{
  setup_fonts();
  setup_textures();

  setup_base();
  setup_main();
  setup_inventory();
  setup_equipment();
  setup_production();
  setup_management();
}


void InterfaceSystem::setup_fonts()
{
  fonts["jura-medium"] = TTF_OpenFont("media/fonts/JuraMedium.ttf", 14);
}


void InterfaceSystem::setup_textures()
{
  textures["interface1"] = load_texture("interface1");
}


SDL_Texture* InterfaceSystem::load_texture(std::string name)
{
  auto path("media/textures/" + name + ".png");

  return IMG_LoadTexture(sdl_interface.renderer, path.c_str());
}


void InterfaceSystem::setup_base()
{
  UIElement _date_and_time;
  _date_and_time.pos = {2, 2};
  _date_and_time.size = {130, 20};
  _date_and_time.text = time_system.get_string();
  _date_and_time.text_texture = "date_and_time_text";

  base_ui_elements.push_back(_date_and_time);
  date_and_time = &base_ui_elements.back();
}


void InterfaceSystem::setup_main()
{
  auto vert_offset(100);
  auto horz_offset(160);

  ScalableElement inventory_button;
  inventory_button.type = "backdrop1";
  inventory_button.pos =
    {SCREEN_SIZE_X / 2 - MAIN_MENU_BUTTON_SIZE_X / 2,
     SCREEN_SIZE_Y / 2 - MAIN_MENU_BUTTON_SIZE_Y / 2 - vert_offset};
  inventory_button.size = {MAIN_MENU_BUTTON_SIZE_X, MAIN_MENU_BUTTON_SIZE_Y};
  inventory_button.texture = "interface1";
  inventory_button.text = "Inventory";
  inventory_button.text_texture = "inventory_button_text";

  create_texture_from_text(inventory_button.text, inventory_button.text_texture);

  main_scalable_elements.push_back(inventory_button);

  ScalableElement equipment_button;
  equipment_button.type = "backdrop1";
  equipment_button.texture = "interface1";
  equipment_button.pos =
    {SCREEN_SIZE_X / 2 - MAIN_MENU_BUTTON_SIZE_X / 2 - horz_offset,
     SCREEN_SIZE_Y / 2 - MAIN_MENU_BUTTON_SIZE_Y / 2};
  equipment_button.size = {MAIN_MENU_BUTTON_SIZE_X, MAIN_MENU_BUTTON_SIZE_Y};
  equipment_button.text = "Equipment";
  equipment_button.text_texture = "equipment_button_text";

  create_texture_from_text(equipment_button.text, equipment_button.text_texture);

  main_scalable_elements.push_back(equipment_button);

  ScalableElement production_button;
  production_button.type = "backdrop1";
  production_button.texture = "interface1";
  production_button.pos =
    {SCREEN_SIZE_X / 2 - MAIN_MENU_BUTTON_SIZE_X / 2,
     SCREEN_SIZE_Y / 2 - MAIN_MENU_BUTTON_SIZE_Y / 2 + vert_offset};
  production_button.size = {MAIN_MENU_BUTTON_SIZE_X, MAIN_MENU_BUTTON_SIZE_Y};
  production_button.text = "Production";
  production_button.text_texture = "production_button_text";

  create_texture_from_text(production_button.text, production_button.text_texture);

  main_scalable_elements.push_back(production_button);

  ScalableElement management_button;
  management_button.type = "backdrop1";
  management_button.texture = "interface1";
  management_button.pos =
    {SCREEN_SIZE_X / 2 - MAIN_MENU_BUTTON_SIZE_X / 2 + horz_offset,
     SCREEN_SIZE_Y / 2 - MAIN_MENU_BUTTON_SIZE_Y / 2};
  management_button.size = {MAIN_MENU_BUTTON_SIZE_X, MAIN_MENU_BUTTON_SIZE_Y};
  management_button.text = "Management";
  management_button.text_texture = "management_button_text";

  create_texture_from_text(management_button.text, management_button.text_texture);

  main_scalable_elements.push_back(management_button);
}


void InterfaceSystem::setup_inventory()
{

}


void InterfaceSystem::setup_equipment()
{

}


void InterfaceSystem::setup_production()
{

}


void InterfaceSystem::setup_management()
{

}


InterfaceSystem::~InterfaceSystem()
{
  for (auto& kv : textures)
    SDL_DestroyTexture(kv.second);
}


void InterfaceSystem::update()
{
  update_date_and_time();

  if (input.menu)
  {
    input.menu = false;
    main_menu_active = !main_menu_active;
  }

  if (main_menu_active)
  {
    if (input.activate)
    {
      if (check_element_for_hit(input.mouse_pos))
      {
	input.activate = false;
      }
    }
  }

  if (input.activate) input.activate = false;
}


bool InterfaceSystem::check_element_for_hit(Vector2i& mouse_pos)
{
  for (auto& element : main_scalable_elements)
  {
    auto hit(
      mouse_pos.x() > element.pos.x() &&
      mouse_pos.x() < element.pos.x() + element.size.x() &&
      mouse_pos.y() > element.pos.y() &&
      mouse_pos.y() < element.pos.y() + element.size.y());

    if (hit)
    {
      if (element.text == "Inventory")
      {
	main_menu_active = false;
	inventory_menu_active = true;
      }
      else if (element.text == "Equipment")
      {
	main_menu_active = false;
	equipment_menu_active = true;
      }
      else if (element.text == "Production")
      {
	main_menu_active = false;
	production_menu_active = true;
      }
      else if (element.text == "Management")
      {
	main_menu_active = false;
	management_menu_active = true;
      }

      return true;
    }
  }

  return false;
}


void InterfaceSystem::create_texture_from_text(string text, string texture_name)
{
  auto surface =
    TTF_RenderText_Blended(
      fonts["jura-medium"], text.c_str(), {236, 255, 255});

  if (textures[texture_name] != nullptr)
    SDL_DestroyTexture(textures[texture_name]);

  textures[texture_name] =
    SDL_CreateTextureFromSurface(sdl_interface.renderer, surface);
}


void InterfaceSystem::update_date_and_time()
{
  date_and_time->text = time_system.get_string();

  create_texture_from_text(date_and_time->text, date_and_time->text_texture);
}


void InterfaceSystem::render()
{
  for (auto& element : base_ui_elements)
    render_element(element);

  for (auto& element : base_scalable_elements)
    render_scalable_element(element);

  if (main_menu_active)
  {
    for (auto& element : main_ui_elements)
      render_element(element);

    for (auto& element : main_scalable_elements)
      render_scalable_element(element);
  }
}


void InterfaceSystem::render_element(UIElement& element)
{
  if (element.texture != "")
  {
    auto& texture(textures[element.texture]);

    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

    SDL_Rect dest_rect;
    dest_rect.x = element.pos.x();
    dest_rect.y = element.pos.y();
    dest_rect.w = element.size.x();
    dest_rect.h = element.size.y();

    SDL_RenderCopy(sdl_interface.renderer, texture, nullptr, &dest_rect);
  }

  if (element.text_texture != "")
  {
    auto& text_texture(textures[element.text_texture]);

    int tw, th;
    SDL_QueryTexture(text_texture, nullptr, nullptr, &tw, &th);

    SDL_Rect text_dest_rect;
    text_dest_rect.x = element.pos.x() + (element.size.x() - tw) / 2;
    text_dest_rect.y = element.pos.y() + (element.size.y() - th) / 2;
    text_dest_rect.w = tw;
    text_dest_rect.h = th;

    SDL_RenderCopy(sdl_interface.renderer, text_texture, nullptr, &text_dest_rect);
  }
}


void InterfaceSystem::render_scalable_element(ScalableElement& element)
{
  auto& clip_data(INTERFACE_CLIP_DATA[element.type]["ct"]);

  SDL_Rect clip_rect;
  clip_rect.x = clip_data.x;
  clip_rect.y = clip_data.y;
  clip_rect.w = clip_data.w;
  clip_rect.h = clip_data.h;

  SDL_Rect dest_rect;
  dest_rect.x = element.pos.x() + element.border;
  dest_rect.y = element.pos.y() + element.border;
  dest_rect.w = element.size.x() - 2 * element.border;
  dest_rect.h = element.size.y() - 2 * element.border;

  SDL_RenderCopy(
    sdl_interface.renderer,
    textures[element.texture],
    &clip_rect, &dest_rect);

  render_scalable_sub_element(element, "tl");
  render_scalable_sub_element(element, "tt");
  render_scalable_sub_element(element, "tr");
  render_scalable_sub_element(element, "rr");
  render_scalable_sub_element(element, "br");
  render_scalable_sub_element(element, "bb");
  render_scalable_sub_element(element, "bl");
  render_scalable_sub_element(element, "ll");

  if (element.text_texture != "")
  {
    auto& text_texture(textures[element.text_texture]);

    int tw, th;
    SDL_QueryTexture(text_texture, nullptr, nullptr, &tw, &th);

    SDL_Rect text_dest_rect;
    text_dest_rect.x = element.pos.x() + (element.size.x() - tw) / 2;
    text_dest_rect.y = element.pos.y() + (element.size.y() - th) / 2;
    text_dest_rect.w = tw;
    text_dest_rect.h = th;

    SDL_RenderCopy(sdl_interface.renderer, text_texture, nullptr, &text_dest_rect);
  }
}


void InterfaceSystem::render_scalable_sub_element(
  ScalableElement& element, string sub_element)
{
  auto& clip_data(INTERFACE_CLIP_DATA[element.type][sub_element]);

  SDL_Rect clip_rect;
  clip_rect.x = clip_data.x;
  clip_rect.y = clip_data.y;
  clip_rect.w = clip_data.w;
  clip_rect.h = clip_data.h;

  SDL_Rect dest_rect;

  if (sub_element == "tr")
  {
    dest_rect.x = element.pos.x() + element.size.x() - element.border;
    dest_rect.y = element.pos.y();
    dest_rect.w = clip_data.w;
    dest_rect.h = clip_data.h;
  }
  else if (sub_element == "br")
  {
    dest_rect.x = element.pos.x() + element.size.x() - element.border;
    dest_rect.y = element.pos.y() + element.size.y() - element.border;
    dest_rect.w = clip_data.w;
    dest_rect.h = clip_data.h;
  }
  else if (sub_element == "bl")
  {
    dest_rect.x = element.pos.x();
    dest_rect.y = element.pos.y() + element.size.y() - element.border;
    dest_rect.w = clip_data.w;
    dest_rect.h = clip_data.h;
  }
  else if (sub_element == "tl")
  {
    dest_rect.x = element.pos.x();
    dest_rect.y = element.pos.y();
    dest_rect.w = clip_data.w;
    dest_rect.h = clip_data.h;
  }
  else if (sub_element == "tt")
  {
    dest_rect.x = element.pos.x() + element.border;
    dest_rect.y = element.pos.y();
    dest_rect.w = element.size.x() - 2 * element.border;
    dest_rect.h = clip_data.h;
  }
  else if (sub_element == "rr")
  {
    dest_rect.x = element.pos.x() + element.size.x() - element.border;
    dest_rect.y = element.pos.y() + element.border;
    dest_rect.w = clip_data.w;
    dest_rect.h = element.size.y() - 2 * element.border;
  }
  else if (sub_element == "bb")
  {
    dest_rect.x = element.pos.x() + element.border;
    dest_rect.y = element.pos.y() + element.size.y() - element.border;
    dest_rect.w = element.size.x() - 2 * element.border;
    dest_rect.h = clip_data.h;
  }
  else if (sub_element == "ll")
  {
    dest_rect.x = element.pos.x();
    dest_rect.y = element.pos.y() + element.border;
    dest_rect.w = clip_data.w;
    dest_rect.h = element.size.y() - 2 * element.border;
  }

  SDL_RenderCopy(
    sdl_interface.renderer,
    textures[element.texture],
    &clip_rect, &dest_rect);
}
