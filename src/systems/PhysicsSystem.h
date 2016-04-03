#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <Box2D/Box2D.h>
#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>
#include <vector>

#include "../components/User.h"
#include "../DebugDraw.h"
#include "EntitySystem.h"
#include "MapSystem.h"

namespace ld
{

constexpr float32 B2D_TIMESTEP(1 / 30.f);
constexpr int32 B2D_VELOCITY_ITERATIONS(1);
constexpr int32 B2D_POSITION_ITERATIONS(1);

class PhysicsSystem
{
  void setup_user_bodies();
  void setup_tile_bodies();
  void setup_door_bodies();

  b2Body* create_body(float x, float y, float hw, float hh);

  std::vector<User>& users;

  MapSystem& map_system;
  EntitySystem& entity_system;

  b2World* world;

public:
  PhysicsSystem(
    std::vector<User>& users, MapSystem& map_system, EntitySystem& entity_system);
  ~PhysicsSystem();

  void update(const double& dt);

  void destroy_body(b2Body* body);
  void set_debug_draw(DebugDraw& debug_draw);
  void render_debug();
};

}

#endif /* PHYSICSSYSTEM_H */
