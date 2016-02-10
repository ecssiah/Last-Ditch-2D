#ifndef ENTITYSYSTEM_H
#define ENTITYSYSTEM_H

#include <random>
#include <vector>

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

  void update_velocities();
  void handle_activation();

  std::mt19937& rng;

  Input& input;
  CameraSystem& camera_system;
  MapSystem& map_system;

  User* active_user;
  std::vector<User> users;

  std::vector<std::string> item_types;

public:
  EntitySystem(
    std::mt19937& rng, Input& input, CameraSystem& camera_system, MapSystem& map_system);

  void update();

  User* get_active_user() { return active_user; }
  std::vector<User>& get_users() { return users; }
};

}

#endif /* ENTITYSYSTEM_H */
