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

constexpr int NUM_ITEMS(100);

class EntitySystem
{
  void setup_users();
  void setup_items();

  void update_users();

  void apply_user_inputs();
  void handle_activation();

  std::string get_random_type();
  void give_random_item(User* user);

  bool find_and_interact_door(Eigen::Vector2f& selection_point, Chunk& chunk);
  bool find_and_interact_item(Eigen::Vector2f& selection_point, Chunk& chunk);

  std::mt19937& rng;

  Input& input;
  CameraSystem& camera_system;
  MapSystem& map_system;

  User active_user;

public:
  EntitySystem(
    std::mt19937& rng, Input& input, CameraSystem& camera_system, MapSystem& map_system);

  void update();

  inline User& get_active_user() { return active_user; }
};

}

#endif /* ENTITYSYSTEM_H */
