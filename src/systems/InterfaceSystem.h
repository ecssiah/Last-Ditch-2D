#ifndef INTERFACESYSTEM_H
#define INTERFACESYSTEM_H

#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <unordered_map>
#include <vector>

#include "../SDL_Interface.h"
#include "../components/UIElement.h"
#include "../components/ScalableElement.h"
#include "../components/User.h"
#include "TimeSystem.h"
#include "EntitySystem.h"

namespace ld
{

class InterfaceSystem
{
  void setup_fonts();
  void setup_textures();
  SDL_Texture* load_texture(std::string name);
  void create_texture_from_text(string text, string texture_name);

  bool check_element_for_hit(Eigen::Vector2i& mouse_pos);

  void setup_base();
  void setup_main();
  void setup_inventory();
  void setup_equipment();
  void setup_production();
  void setup_management();

  void update_date_and_time();

  void render_element(UIElement& element);
  void render_scalable_element(ScalableElement& element);
  void render_scalable_sub_element(ScalableElement& element, string sub_element);

  Input& input;
  SDL_Interface& sdl_interface;
  TimeSystem& time_system;
  CameraSystem& camera_system;
  EntitySystem& entity_system;

  bool main_menu_active;
  bool inventory_menu_active;
  bool equipment_menu_active;
  bool production_menu_active;
  bool management_menu_active;
  bool status_menu_active;

  User* active_user;

  std::unordered_map<std::string, TTF_Font*> fonts;
  std::unordered_map<std::string, SDL_Texture*> textures;

  std::vector<UIElement> base_ui_elements;
  std::vector<ScalableElement> base_scalable_elements;

  UIElement* date_and_time;

  std::vector<UIElement> main_ui_elements;
  std::vector<ScalableElement> main_scalable_elements;

  std::vector<UIElement> inventory_ui_elements;
  std::vector<ScalableElement> inventory_scalable_elements;

  std::vector<UIElement> equipment_ui_elements;
  std::vector<ScalableElement> equipment_scalable_elements;

  std::vector<UIElement> production_ui_elements;
  std::vector<ScalableElement> production_scalable_elements;

  std::vector<UIElement> management_ui_elements;
  std::vector<ScalableElement> management_scalable_elements;

public:
  InterfaceSystem(
    SDL_Interface& sdl_interface, Input& input,
    TimeSystem& time_system, CameraSystem& camera_system, EntitySystem& entity_system);
  ~InterfaceSystem();

  void update();
  void render();
};

}

#endif /* INTERFACESYSTEM_H */
