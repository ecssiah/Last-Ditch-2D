#include "ConfigurationSystem.h"

#include <string>
#include <yaml-cpp/yaml.h>

#include "../constants/ItemConstants.h"
#include "../constants/MapConstants.h"
#include "../constants/RenderConstants.h"
#include "../constants/UserConstants.h"
#include "../constants/UIConstants.h"

using namespace ld;

ConfigurationSystem::ConfigurationSystem()
{
  load_weapon_data();
  load_apparel_data();
  load_utility_data();
  load_resource_data();
  load_tile_data();
  load_user_data();
}


void ConfigurationSystem::load_resource_data()
{
  const auto resource_info(YAML::LoadFile("scripts/resources.yml"));

  for (auto kv : resource_info)
  {
    YAML::Node resource_data_map(kv.second);

    ResourceInfo resource_info_entry;
    resource_info_entry.name = resource_data_map["name"].as<std::string>();
    resource_info_entry.texture = resource_data_map["texture"].as<std::string>();
    resource_info_entry.category = resource_data_map["category"].as<std::string>();
    resource_info_entry.value = resource_data_map["value"].as<float>();
    resource_info_entry.weight = resource_data_map["weight"].as<float>();
    resource_info_entry.volume = resource_data_map["volume"].as<float>();

    SDL_Rect clip_rect;
    clip_rect.x = resource_data_map["uv"][0].as<int>() * HALF_UNIT;
    clip_rect.x = resource_data_map["uv"][1].as<int>() * HALF_UNIT;
    clip_rect.w = HALF_UNIT;
    clip_rect.h = HALF_UNIT;

    resource_info_entry.clip_rect = clip_rect;

    auto type(kv.first.as<std::string>());

    Resource_Types.push_back(type);
    Resource_Data[type] = resource_info_entry;

    Item_Types.push_back(type);
    Item_Data["resource"][type] = resource_info_entry;
  }
}


void ConfigurationSystem::load_utility_data()
{
  const auto utility_info(YAML::LoadFile("scripts/utilities.yml"));

  for (auto kv : utility_info)
  {
    YAML::Node utility_data_map(kv.second);

    UtilityInfo utility_info_entry;
    utility_info_entry.name = utility_data_map["name"].as<std::string>();
    utility_info_entry.texture = utility_data_map["texture"].as<std::string>();
    utility_info_entry.category = utility_data_map["category"].as<std::string>();
    utility_info_entry.value = utility_data_map["value"].as<float>();
    utility_info_entry.weight = utility_data_map["weight"].as<float>();
    utility_info_entry.volume = utility_data_map["volume"].as<float>();

    for (auto kv_effect : utility_data_map["effects"])
    {
      auto effect_type(kv_effect.first.as<std::string>());
      auto effect_value(kv_effect.second[0].as<float>());
      auto effect_duration(kv_effect.second[1].as<unsigned>());

      Effect effect;
      effect.type = effect_type;
      effect.value = effect_value;
      effect.duration = effect_duration;

      utility_info_entry.effects.push_back(effect);
    }

    SDL_Rect clip_rect;
    clip_rect.x = utility_data_map["uv"][0].as<int>() * HALF_UNIT;
    clip_rect.x = utility_data_map["uv"][1].as<int>() * HALF_UNIT;
    clip_rect.w = HALF_UNIT;
    clip_rect.h = HALF_UNIT;

    utility_info_entry.clip_rect = clip_rect;

    auto type(kv.first.as<std::string>());

    Utility_Types.push_back(type);
    Utility_Data[type] = utility_info_entry;
  }
}


void ConfigurationSystem::load_weapon_data()
{
  const auto weapon_info(YAML::LoadFile("scripts/weapons.yml"));

  for (auto kv : weapon_info)
  {
    YAML::Node weapon_data_map(kv.second);

    SDL_Rect clip_rect;
    clip_rect.x = weapon_data_map["uv"][0].as<int>() * HALF_UNIT;
    clip_rect.x = weapon_data_map["uv"][1].as<int>() * HALF_UNIT;
    clip_rect.w = HALF_UNIT;
    clip_rect.h = HALF_UNIT;

    WeaponInfo weapon_info_entry;
    weapon_info_entry.name = weapon_data_map["name"].as<std::string>();
    weapon_info_entry.texture = weapon_data_map["texture"].as<std::string>();
    weapon_info_entry.category = weapon_data_map["category"].as<std::string>();
    weapon_info_entry.value = weapon_data_map["value"].as<float>();
    weapon_info_entry.weight = weapon_data_map["weight"].as<float>();
    weapon_info_entry.volume = weapon_data_map["volume"].as<float>();
    weapon_info_entry.clip_rect = clip_rect;
    weapon_info_entry.physical_damage = weapon_data_map["physical_damage"].as<float>();
    weapon_info_entry.energy_damage = weapon_data_map["energy_damage"].as<float>();
    weapon_info_entry.heat_damage = weapon_data_map["heat_damage"].as<float>();
    weapon_info_entry.cold_damage = weapon_data_map["cold_damage"].as<float>();

    auto type(kv.first.as<std::string>());

    Weapon_Types.push_back(type);
    Weapon_Data[type] = weapon_info_entry;
  }
}


void ConfigurationSystem::load_tile_data()
{
  const auto tile_info(YAML::LoadFile("scripts/tiles.yml"));

  for (auto kv : tile_info)
  {
    YAML::Node tile_data_map(kv.second);

    TileInfo tile_info_entry;
    tile_info_entry.texture = tile_data_map["texture"].as<std::string>();

    SDL_Rect clip_rect;
    clip_rect.x = tile_data_map["uv"][0].as<int>() * PIXELS_PER_UNIT;
    clip_rect.x = tile_data_map["uv"][1].as<int>() * PIXELS_PER_UNIT;
    clip_rect.w = PIXELS_PER_UNIT;
    clip_rect.h = PIXELS_PER_UNIT;

    tile_info_entry.clip_rect = clip_rect;

    auto type(kv.first.as<std::string>());

    Tile_Data[type] = tile_info_entry;
  }
}


void ConfigurationSystem::load_user_data()
{
  const auto user_info(YAML::LoadFile("scripts/user.yml"));

  for (auto kv : user_info)
  {
    YAML::Node user_data_map(kv.second);

    UserInfo user_info_entry;
    user_info_entry.name = user_data_map["name"].as<std::string>();
    user_info_entry.texture = user_data_map["texture"].as<std::string>();

    for (auto animation_kv : user_data_map["animation_data"])
    {
      YAML::Node user_animation_map(animation_kv.second);

      auto animation_type(kv.first.as<std::string>());

      AnimationInfo animation_info_entry;
      animation_info_entry.frames = user_animation_map["frames"].as<unsigned>();

      SDL_Rect clip_rect;
      clip_rect.x = user_animation_map["uv"][0].as<unsigned>() * PIXELS_PER_UNIT;
      clip_rect.y = user_animation_map["uv"][1].as<unsigned>() * PIXELS_PER_UNIT;
      clip_rect.w = PIXELS_PER_UNIT;
      clip_rect.h = PIXELS_PER_UNIT;

      animation_info_entry.clip_rect = clip_rect;

      user_info_entry.animation_data[animation_type] = animation_info_entry;
    }

    auto type(kv.first.as<std::string>());

    User_Data[type] = user_info_entry;
  }
}


void ConfigurationSystem::load_element_data()
{
  const auto element_info(YAML::LoadFile("scripts/ui.yml"));

  for (auto kv : element_info)
  {
    YAML::Node element_data_map(kv.second);

    auto type(kv.first.as<std::string>());

    ElementInfo element_info_entry;
    element_info_entry.texture = element_data_map["texture"].as<std::string>();

    SDL_Rect clip_rect;
    clip_rect.x = element_data_map["uv"][0].as<unsigned>() * PIXELS_PER_UNIT;
    clip_rect.y = element_data_map["uv"][1].as<unsigned>() * PIXELS_PER_UNIT;
    clip_rect.w = PIXELS_PER_UNIT;
    clip_rect.h = PIXELS_PER_UNIT;

    element_info_entry.clip_rect = clip_rect;

    Element_Data[type] = element_info_entry;
  }
}
