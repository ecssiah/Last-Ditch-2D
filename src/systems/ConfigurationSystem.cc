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
  load_item_data();
  load_tile_data();
  load_user_data();

  printf("\nConfigurationSystem ready\n");
}


void ConfigurationSystem::load_item_data()
{
  YAML::Node item_data_node(YAML::LoadFile("scripts/items.yml"));

  for (auto kv : item_data_node)
  {
    YAML::Node item_info_node(kv.second);

    SDL_Rect clip_rect;
    clip_rect.x = item_info_node["uv"][0].as<int>() * HALF_UNIT;
    clip_rect.x = item_info_node["uv"][1].as<int>() * HALF_UNIT;
    clip_rect.w = HALF_UNIT;
    clip_rect.h = HALF_UNIT;

    ItemInfo item_info_entry;
    item_info_entry.name = item_info_node["name"].as<std::string>();
    item_info_entry.texture = item_info_node["texture"].as<std::string>();
    item_info_entry.category = item_info_node["category"].as<std::string>();
    item_info_entry.value = item_info_node["value"].as<float>();
    item_info_entry.weight = item_info_node["weight"].as<float>();
    item_info_entry.volume = item_info_node["volume"].as<float>();
    item_info_entry.clip_rect = clip_rect;

    auto type(kv.first.as<std::string>());

    Item_Types.push_back(type);
    Item_Data[type] = item_info_entry;
  }
}


void ConfigurationSystem::load_tile_data()
{
  YAML::Node tile_data_node(YAML::LoadFile("scripts/tiles.yml"));

  for (auto kv : tile_data_node)
  {
    YAML::Node tile_info_node(kv.second);

    SDL_Rect clip_rect;
    clip_rect.x = tile_info_node["uv"][0].as<int>() * PIXELS_PER_UNIT;
    clip_rect.x = tile_info_node["uv"][1].as<int>() * PIXELS_PER_UNIT;
    clip_rect.w = PIXELS_PER_UNIT;
    clip_rect.h = PIXELS_PER_UNIT;

    TileInfo tile_info_entry;
    tile_info_entry.texture = tile_info_node["texture"].as<std::string>();
    tile_info_entry.clip_rect = clip_rect;

    auto type(kv.first.as<std::string>());

    Tile_Data[type] = tile_info_entry;
  }
}


void ConfigurationSystem::load_animation_data(
  UserInfo& user_info_entry, YAML::Node& user_info_node)
{
  YAML::Node animation_data_node(user_info_node["animation_data"]);

  for (auto kv : animation_data_node)
  {
    YAML::Node animation_info_node(kv.second);

    SDL_Rect clip_rect;
    clip_rect.x = animation_info_node["uv"][0].as<unsigned>() * PIXELS_PER_UNIT;
    clip_rect.y = animation_info_node["uv"][1].as<unsigned>() * PIXELS_PER_UNIT;
    clip_rect.w = PIXELS_PER_UNIT;
    clip_rect.h = PIXELS_PER_UNIT;

    AnimationInfo animation_info_entry;
    animation_info_entry.frames = animation_info_node["frames"].as<unsigned>();
    animation_info_entry.clip_rect = clip_rect;

    auto type(kv.first.as<std::string>());

    user_info_entry.animation_data[type] = animation_info_entry;
  }
}


void ConfigurationSystem::load_user_data()
{
  YAML::Node user_data_node(YAML::LoadFile("scripts/users.yml"));

  for (auto kv : user_data_node)
  {
    YAML::Node user_info_node(kv.second);

    UserInfo user_info_entry;
    user_info_entry.name = user_info_node["name"].as<std::string>();
    user_info_entry.texture = user_info_node["texture"].as<std::string>();

    load_animation_data(user_info_entry, user_info_node);

    auto type(kv.first.as<std::string>());

    User_Data[type] = user_info_entry;
  }
}


void ConfigurationSystem::load_element_data()
{
  YAML::Node element_data(YAML::LoadFile("scripts/ui.yml"));

  for (auto kv : element_data)
  {
    YAML::Node element_data_map(kv.second);

    SDL_Rect clip_rect;
    clip_rect.x = element_data_map["uv"][0].as<unsigned>() * PIXELS_PER_UNIT;
    clip_rect.y = element_data_map["uv"][1].as<unsigned>() * PIXELS_PER_UNIT;
    clip_rect.w = PIXELS_PER_UNIT;
    clip_rect.h = PIXELS_PER_UNIT;

    ElementInfo element_info_entry;
    element_info_entry.texture = element_data_map["texture"].as<std::string>();
    element_info_entry.clip_rect = clip_rect;

    auto type(kv.first.as<std::string>());

    Element_Data[type] = element_info_entry;
  }
}
