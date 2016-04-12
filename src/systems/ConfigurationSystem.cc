#include "ConfigurationSystem.h"

#include <string>
#include <yaml-cpp/yaml.h>

#include "../Utils.h"
#include "../constants/ItemConstants.h"
#include "../constants/MapConstants.h"
#include "../constants/RenderConstants.h"
#include "../constants/UserConstants.h"
#include "../constants/UIConstants.h"

namespace ld
{

ConfigurationSystem::ConfigurationSystem()
{
  load_item_data();
  load_tile_data();
  load_user_data();

  load_font_data();

  printf("\nConfigurationSystem ready\n");
}


void ConfigurationSystem::load_item_data()
{
  YAML::Node item_data(YAML::LoadFile("scripts/items.yml"));

  for (auto kv : item_data)
  {
    YAML::Node item_info(kv.second);

    SDL_Rect clip_rect;
    clip_rect.x = item_info["uv"][0].as<int>() * HALF_UNIT;
    clip_rect.y = item_info["uv"][1].as<int>() * HALF_UNIT;
    clip_rect.w = HALF_UNIT;
    clip_rect.h = HALF_UNIT;

    ItemInfo item_info_entry;
    item_info_entry.name = item_info["name"].as<std::string>();
    item_info_entry.texture = item_info["texture"].as<std::string>();
    item_info_entry.category = item_info["category"].as<std::string>();
    item_info_entry.value = item_info["value"].as<float>();
    item_info_entry.weight = item_info["weight"].as<float>();
    item_info_entry.volume = item_info["volume"].as<float>();
    item_info_entry.clip_rect = clip_rect;

    auto type(kv.first.as<std::string>());

    Item_Types.push_back(type);
    Item_Data[type] = item_info_entry;
  }
}


void ConfigurationSystem::load_tile_data()
{
  YAML::Node tile_data(YAML::LoadFile("scripts/tiles.yml"));

  for (auto kv : tile_data)
  {
    YAML::Node tile_info(kv.second);

    SDL_Rect clip_rect;
    clip_rect.x = tile_info["uv"][0].as<int>() * PIXELS_PER_UNIT;
    clip_rect.y = tile_info["uv"][1].as<int>() * PIXELS_PER_UNIT;
    clip_rect.w = PIXELS_PER_UNIT;
    clip_rect.h = PIXELS_PER_UNIT;

    TileInfo tile_info_entry;
    tile_info_entry.texture = tile_info["texture"].as<std::string>();
    tile_info_entry.clip_rect = clip_rect;

    auto type(kv.first.as<std::string>());

    Tile_Data[type] = tile_info_entry;
  }
}


void ConfigurationSystem::load_animation_data(
  UserInfo& user_info_entry, YAML::Node& user_info)
{
  YAML::Node animation_data(user_info["animation_data"]);

  for (auto kv : animation_data)
  {
    YAML::Node animation_info(kv.second);

    SDL_Rect clip_rect;
    clip_rect.x = animation_info["uv"][0].as<unsigned>() * PIXELS_PER_UNIT;
    clip_rect.y = animation_info["uv"][1].as<unsigned>() * PIXELS_PER_UNIT;
    clip_rect.w = PIXELS_PER_UNIT;
    clip_rect.h = PIXELS_PER_UNIT;

    AnimationInfo animation_info_entry;
    animation_info_entry.frames = animation_info["frames"].as<unsigned>();
    animation_info_entry.clip_rect = clip_rect;

    auto type(kv.first.as<std::string>());

    user_info_entry.animation_data[type] = animation_info_entry;
  }
}


void ConfigurationSystem::load_user_data()
{
  YAML::Node user_data(YAML::LoadFile("scripts/users.yml"));

  for (auto kv : user_data)
  {
    YAML::Node user_info(kv.second);

    UserInfo user_info_entry;
    user_info_entry.name = user_info["name"].as<std::string>();
    user_info_entry.texture = user_info["texture"].as<std::string>();

    load_animation_data(user_info_entry, user_info);

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

    ScalableInfo scalable_info_entry;
    scalable_info_entry.texture = element_data_map["texture"].as<std::string>();

    for (auto _kv : element_data_map["sub-elements"])
    {
      auto _type(_kv.first.as<std::string>());

      auto& clip_rect(scalable_info_entry.clip_rects[_type]);
      clip_rect.x = _kv.second[0].as<int>();
      clip_rect.y = _kv.second[1].as<int>();
      clip_rect.w = _kv.second[2].as<int>();
      clip_rect.h = _kv.second[3].as<int>();
    }

    auto type(kv.first.as<std::string>());

    Scalable_Data[type] = scalable_info_entry;
  }
}


void ConfigurationSystem::load_font_data()
{
  YAML::Node font_data(YAML::LoadFile("media/fonts/Jura.yml"));

  for (auto kv : font_data)
  {
    auto character(kv.first.as<char>());

    SDL_Rect clip_rect;
    clip_rect.x = kv.second[0].as<int>();
    clip_rect.y = kv.second[1].as<int>();
    clip_rect.w = kv.second[2].as<int>();
    clip_rect.h = kv.second[3].as<int>();

    Font_Data[character] = clip_rect;
  }
}


}
