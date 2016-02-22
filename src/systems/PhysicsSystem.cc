#include "PhysicsSystem.h"

#include <eigen3/Eigen/Geometry>
#include <iostream>

#include "../constants/MapConstants.h"

using namespace ld;
using namespace Eigen;
using namespace std;

PhysicsSystem::PhysicsSystem(
  SDL_Renderer* _renderer, MapSystem& _map_system, EntitySystem& _entity_system
)
  : map_system(_map_system),
    entity_system(_entity_system),
    world(new b2World({0, 0}))
{
  setup_user_bodies();
  setup_tile_bodies();
  setup_door_bodies();

  cout << "PhysicsSystem ready" << endl;
}


PhysicsSystem::~PhysicsSystem()
{
  delete world;
}


void PhysicsSystem::update(double dt)
{
  if (map_system.is_dirty())
  {
    map_system.set_dirty(false);

    for (auto floor(0); floor < NUM_FLOORS; ++floor)
    {
      for (auto cx(0); cx < MAP_SIZE_X; ++cx)
      {
	for (auto cy(0); cy < MAP_SIZE_Y; ++cy)
	{
	  auto& chunk(map_system.get_chunk(cx, cy, floor));

	  if (chunk.dirty)
	  {
	    chunk.dirty = false;

	    for (auto x(0); x < TILES_PER_CHUNK_X; ++x)
	    {
	      for (auto y(0); y < TILES_PER_CHUNK_Y; ++y)
	      {
		auto& tile(chunk.main_tiles[x][y]);

		if (tile.dirty)
		{
		  tile.dirty = false;

		  if (tile.solid)
		  {
		    tile.body = create_body(tile.pos.x(), tile.pos.y(), .5, .5);
		  }
		  else
		  {
		    destroy_body(tile.body);
		    tile.body = nullptr;
		  }
		}
	      }
	    }

	    for (auto& door : chunk.doors)
	    {
	      if (door.dirty)
	      {
		door.dirty = false;

		if (door.solid)
		{
		  door.body = create_body(door.pos.x(), door.pos.y(), .5, .5);
		}
		else
		{
		  destroy_body(door.body);
		  door.body = nullptr;
		}
	      }
	    }
	  }
	}
      }
    }
  }

  for (auto floor(0); floor < NUM_FLOORS; ++floor)
  {
    auto& users(entity_system.get_users(floor));

    for (auto& user : users)
    {
      b2Vec2 impulse(dt * user.vel.x(), dt * user.vel.y());
      user.body->ApplyLinearImpulse(impulse, user.body->GetWorldCenter(), true);
    }

  }

  world->Step(B2D_TIMESTEP, B2D_VELOCITY_ITERATIONS, B2D_POSITION_ITERATIONS);
  world->ClearForces();

  for (auto floor(0); floor < NUM_FLOORS; ++floor)
  {
    auto& users(entity_system.get_users(floor));

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


void PhysicsSystem::setup_user_bodies()
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


void PhysicsSystem::setup_tile_bodies()
{
  for (auto floor(0); floor < NUM_FLOORS; ++floor)
  {
    for (auto x(0); x < MAP_SIZE_X; ++x)
    {
      for (auto y(0); y < MAP_SIZE_Y; ++y)
      {
	auto& tile(map_system.get_main_tile(x, y, floor));

	if (tile.solid)
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

	  tile.body = body;
	}
      }
    }
  }
}


void PhysicsSystem::setup_door_bodies()
{
  for (auto floor(0); floor < NUM_FLOORS; ++floor)
  {
    for (auto x(0); x < MAP_SIZE_X; x += TILES_PER_CHUNK_X)
    {
      for (auto y(0); y < MAP_SIZE_Y; y += TILES_PER_CHUNK_Y)
      {
	auto& chunk(map_system.get_chunk(x, y, floor));

	for (auto& door : chunk.doors)
	{
	  if (door.solid)
	  {
	    b2BodyDef body_def;
	    body_def.type = b2_staticBody;
	    body_def.position.Set(door.pos.x(), door.pos.y());
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

	    door.body = body;
	  }
	}
      }
    }
  }
}


b2Body* PhysicsSystem::create_body(float x, float y, float hw, float hh)
{
  b2BodyDef body_def;
  body_def.type = b2_staticBody;
  body_def.position.Set(x, y);
  body_def.allowSleep = true;
  body_def.fixedRotation = true;
  body_def.active = true;

  auto body(world->CreateBody(&body_def));

  b2PolygonShape polygon_shape;
  polygon_shape.SetAsBox(hw, hh);

  b2FixtureDef fixture_def;
  fixture_def.shape = &polygon_shape;
  fixture_def.friction = 0;

  body->CreateFixture(&fixture_def);

  return body;
}


void PhysicsSystem::destroy_body(b2Body* body)
{
  world->DestroyBody(body);
}
