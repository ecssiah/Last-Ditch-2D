#ifndef ENTITYSYSTEM_H
#define ENTITYSYSTEM_H

#include <random>
#include <vector>

#include "../components/DynamicEntity.h"
#include "../components/StaticEntity.h"
#include "../components/Input.h"
#include "../systems/MapSystem.h"

namespace ld
{

constexpr int NUM_ITEMS = 100;

class EntitySystem
{
  void setup_users();
  void setup_items();
  std::string get_random_type();

  std::mt19937& rng;

  Input& input;
  MapSystem& map_system;

  DynamicEntity* active_user;

  std::vector<DynamicEntity> dynamic_entities;
  std::vector<StaticEntity> items;

  std::vector<std::string> item_types;

public:
  EntitySystem(std::mt19937& rng, Input& input, MapSystem& map_system);

  void update();

  DynamicEntity* get_active_user() { return active_user; }
  std::vector<DynamicEntity>& get_dynamic_entities() { return dynamic_entities; }
  std::vector<StaticEntity>& get_items() { return items; }
};

}

#endif /* ENTITYSYSTEM_H */
