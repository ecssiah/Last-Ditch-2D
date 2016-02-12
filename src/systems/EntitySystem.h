#ifndef ENTITYSYSTEM_H
#define ENTITYSYSTEM_H

#include <random>
#include <vector>

#include "../components/Door.h"
#include "../components/Entity.h"
#include "../components/Input.h"
#include "../components/User.h"
#include "../systems/MapSystem.h"
#include "../systems/CameraSystem.h"

namespace ld
{

constexpr int NUM_ITEMS = 100;

class EntitySystem
{
  void setup_users();
  void setup_items();
  std::string get_random_type();

  void apply_user_inputs();
  void handle_activation();
  void handle_door(Entity& entity);

  std::mt19937& rng;

  Input& input;
  CameraSystem& camera_system;
  MapSystem& map_system;

  User* active_user;
  std::vector<std::vector<User>> users;

  std::vector<std::string> item_types;

public:
  EntitySystem(
    std::mt19937& rng, Input& input, CameraSystem& camera_system, MapSystem& map_system);

  void update();

  inline User* get_active_user() { return active_user; }
  inline std::vector<User>& get_users(int floor) { return users[floor]; }
};

}

#endif /* ENTITYSYSTEM_H */
