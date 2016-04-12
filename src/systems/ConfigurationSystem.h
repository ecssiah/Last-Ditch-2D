#ifndef CONFIGURATIONSYSTEM_H
#define CONFIGURATIONSYSTEM_H

#include <yaml-cpp/yaml.h>

#include "../components/info/UserInfo.h"

namespace ld
{

class ConfigurationSystem
{
  void load_item_data();
  void load_tile_data();
  void load_animation_data(UserInfo& user_info_entry, YAML::Node& animation_data);
  void load_user_data();
  void load_element_data();

  void load_font_data();

public:
  ConfigurationSystem();
};

}

#endif /* CONFIGURATIONSYSTEM_H */
