#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <Box2D/Box2D.h>
#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>

#include "../DebugDraw.h"
#include "EntitySystem.h"
#include "MapSystem.h"

namespace ld
{

constexpr float32 B2D_TIMESTEP = 1 / 30.f;
constexpr int32 B2D_VELOCITY_ITERATIONS = 8;
constexpr int32 B2D_POSITION_ITERATIONS = 3;

class PhysicsSystem
{
  void setup_static_bodies();
  void setup_dynamic_bodies();

  void cleanup_dirty_entities();

  MapSystem& map_system;
  EntitySystem& entity_system;

  b2World* world;

public:
  PhysicsSystem(SDL_Renderer* renderer, MapSystem& map_system, EntitySystem& entity_system);
  ~PhysicsSystem();

  void update(double dt);

  void destroy_body(b2Body* body);
  void set_debug_draw(DebugDraw& debug_draw);
  void render_debug();
};

}

#endif /* PHYSICSSYSTEM_H */
