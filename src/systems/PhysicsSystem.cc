#include "PhysicsSystem.h"

#include <eigen3/Eigen/Geometry>
#include <iostream>

#include "../constants/MapConstants.h"

using namespace ld;
using namespace Eigen;
using namespace std;

PhysicsSystem::PhysicsSystem(
  SDL_Renderer* renderer, MapSystem& map_system_, EntitySystem& entity_system_
)
  : map_system(map_system_),
    entity_system(entity_system_),
    world(new b2World({0, 0}))
{
  setup_dynamic_bodies();
  setup_static_bodies();

  cout << "Physics system ready" << endl;
}


PhysicsSystem::~PhysicsSystem()
{
  delete world;
}


void PhysicsSystem::update(double dt)
{
  for (auto floor(0); floor < NUM_FLOORS; ++floor)
  {
    auto& users(entity_system.get_users(floor));

    for (auto& user : users)
    {
      b2Vec2 impulse(dt * user.vel.x(), dt * user.vel.y());
      user.body->ApplyLinearImpulse(impulse, user.body->GetWorldCenter(), true);
    }

    world->Step(B2D_TIMESTEP, B2D_VELOCITY_ITERATIONS, B2D_POSITION_ITERATIONS);
    world->ClearForces();

    for (auto& user : users)
      user.pos = {user.body->GetPosition().x, user.body->GetPosition().y};
  }
}


void PhysicsSystem::set_debug_draw(DebugDraw& debug_draw)
{
  world->SetDebugDraw(&debug_draw);
}


void PhysicsSystem::render_debug()
{
  world->DrawDebugData();
}


void PhysicsSystem::setup_dynamic_bodies()
{
  for (auto floor(0); floor < NUM_FLOORS; ++floor)
  {
    for (auto& user : entity_system.get_users(floor))
    {
      b2BodyDef body_def;
      body_def.type = b2_dynamicBody;
      body_def.position.Set(user.pos.x(), user.pos.y());
      body_def.linearDamping = 8;
      body_def.allowSleep = true;
      body_def.fixedRotation = true;
      body_def.active = true;

      auto body(world->CreateBody(&body_def));

      b2CircleShape circle_shape;
      circle_shape.m_radius = user.radius;

      b2FixtureDef fixture_def;
      fixture_def.shape = &circle_shape;
      fixture_def.friction = 0;

      body->CreateFixture(&fixture_def);

      user.body = body;
    }
  }
}


void PhysicsSystem::setup_static_bodies()
{
  for (auto floor(0); floor < NUM_FLOORS; ++floor)
  {
    for (auto x(0); x < MAP_SIZE_X; ++x)
    {
      for (auto y(0); y < MAP_SIZE_Y; ++y)
      {
	auto& entity(map_system.get_entity(x, y, floor));

	if (entity.solid)
	{
	  b2BodyDef body_def;
	  body_def.type = b2_staticBody;
	  body_def.position.Set(x, y);
	  body_def.allowSleep = true;
	  body_def.fixedRotation = true;
	  body_def.active = true;

	  auto body(world->CreateBody(&body_def));

	  b2PolygonShape polygon_shape;
	  polygon_shape.SetAsBox(.5, .5);

	  b2FixtureDef fixture_def;
	  fixture_def.shape = &polygon_shape;
	  fixture_def.friction = 0;

	  body->CreateFixture(&fixture_def);

	  entity.body = body;
	}
      }
    }
  }
}


void PhysicsSystem::destroy_body(b2Body* body)
{
  world->DestroyBody(body);
}
