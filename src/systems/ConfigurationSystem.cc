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

  load_ui_element_data();
}


void ConfigurationSystem::load_item_data()
{
  const auto item_info(YAML::LoadFile("scripts/items.yml"));

  for (auto kv : item_info)
  {
    YAML::Node item_data_map(kv.second);

    ItemInfo item_info_entry;
    item_info_entry.name = item_data_map["name"].as<std::string>();
    item_info_entry.texture = item_data_map["texture"].as<std::string>();
    item_info_entry.category = item_data_map["category"].as<std::string>();
    item_info_entry.value = item_data_map["value"].as<float>();
    item_info_entry.quality = item_data_map["quality"].as<float>();
    item_info_entry.weight = item_data_map["weight"].as<float>();
    item_info_entry.volume = item_data_map["volume"].as<float>();

    SDL_Rect clip_rect;
    clip_rect.x = item_data_map["uv"][0].as<int>() * HALF_UNIT;
    clip_rect.x = item_data_map["uv"][1].as<int>() * HALF_UNIT;
    clip_rect.w = HALF_UNIT;
    clip_rect.h = HALF_UNIT;

    item_info_entry.clip_rect = clip_rect;

    auto type(kv.first.as<std::string>());
    Item_Types.push_back(type);

    Item_Data[type] = item_info_entry;
  }
}


void ConfigurationSystem::load_tile_data()
{
  const auto tile_info(YAML::LoadFile("scripts/tiles.yml"));

  for (auto kv : tile_info)
  {
    YAML::Node tile_data_map(kv.second);

    auto type(kv.first.as<std::string>());

    TileInfo tile_info_entry;
    tile_info_entry.texture = tile_data_map["texture"].as<std::string>();

    SDL_Rect clip_rect;
    clip_rect.x = tile_data_map["uv"][0].as<int>() * PIXELS_PER_UNIT;
    clip_rect.x = tile_data_map["uv"][1].as<int>() * PIXELS_PER_UNIT;
    clip_rect.w = PIXELS_PER_UNIT;
    clip_rect.h = PIXELS_PER_UNIT;

    tile_info_entry.clip_rect = clip_rect;

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


void ConfigurationSystem::load_ui_element_data()
{
  const auto ui_element_info(YAML::LoadFile("scripts/ui.yml"));

  for (auto kv : ui_element_info)
  {
    YAML::Node ui_element_data_map(kv.second);

    auto type(kv.first.as<std::string>());

    UIElementInfo ui_element_info_entry;
    ui_element_info_entry.texture = ui_element_data_map["texture"].as<std::string>();

    SDL_Rect clip_rect;
    clip_rect.x = ui_element_data_map["uv"][0].as<unsigned>() * PIXELS_PER_UNIT;
    clip_rect.y = ui_element_data_map["uv"][1].as<unsigned>() * PIXELS_PER_UNIT;
    clip_rect.w = PIXELS_PER_UNIT;
    clip_rect.h = PIXELS_PER_UNIT;

    ui_element_info_entry.clip_rect = clip_rect;

    UIElementData[type] = ui_element_info_entry;
  }
}
