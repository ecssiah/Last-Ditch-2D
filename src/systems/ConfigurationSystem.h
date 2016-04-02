#ifndef CONFIGURATIONSYSTEM_H
#define CONFIGURATIONSYSTEM_H

namespace ld
{

class ConfigurationSystem
{
  void load_item_data();
  void load_map_data();
  void load_user_data();
  void load_ui_element_data();

public:
  ConfigurationSystem();
};

}

#endif /* CONFIGURATIONSYSTEM_H */
