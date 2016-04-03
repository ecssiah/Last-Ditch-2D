#ifndef CONFIGURATIONSYSTEM_H
#define CONFIGURATIONSYSTEM_H

namespace ld
{

class ConfigurationSystem
{
  void load_weapon_data();
  void load_apparel_data();
  void load_utility_data();
  void load_resource_data();
  void load_tile_data();
  void load_user_data();
  void load_element_data();

public:
  ConfigurationSystem();
};

}

#endif /* CONFIGURATIONSYSTEM_H */
