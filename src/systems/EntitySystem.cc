#include "EntitySystem.h"

#include <cassert>
#include <eigen3/Eigen/Geometry>
#include <iostream>
#include <random>

#include "../components/Door.h"
#include "../components/Item.h"
#include "../constants/ItemConstants.h"
#include "../constants/MapConstants.h"
#include "../constants/RenderConstants.h"

using namespace ld;
using namespace Eigen;
using namespace std;

EntitySystem::EntitySystem(
  mt19937& rng_, Input& input_, CameraSystem& camera_system_, MapSystem& map_system_
)
  : rng(rng_),
    input(input_),
    map_system(map_system_),
    camera_system(camera_system_),
    active_user(nullptr),
    users(NUM_FLOORS)
{
  setup_users();
  setup_items();

  cout << "Entity system ready" << endl;
}


void EntitySystem::setup_users()
{
  User kadijah;
  kadijah.name = "Kadijah";
  kadijah.type = "kadijah";
  kadijah.texture_name = TYPE_TO_TEXTURE[kadijah.type];
  kadijah.pos = {1, 2};
  kadijah.floor = 0;
  kadijah.radius = .48;
  kadijah.speed = 240;
  kadijah.clip_rect.w = PIXELS_PER_UNIT;
  kadijah.clip_rect.h = PIXELS_PER_UNIT;

  users[kadijah.floor].push_back(kadijah);
  active_user = &users[kadijah.floor].back();
}


std::string EntitySystem::get_random_type()
{
  uniform_int_distribution<> type_dist(0, ITEM_TYPES.size() - 1);

  return ITEM_TYPES[type_dist(rng)];
}


void EntitySystem::setup_items()
{
  for (auto floor(0); floor < NUM_FLOORS; ++floor)
  {
    for (auto i(0); i < NUM_ITEMS; ++i)
    {
      uniform_real_distribution<> x_dist(0, MAP_SIZE_X - 1);
      uniform_real_distribution<> y_dist(0, MAP_SIZE_Y - 1);

      Item item;
      item.type = get_random_type();
      item.texture_name = TYPE_TO_TEXTURE[item.type];
      item.properties.item = true;
      item.floor = floor;

      while (1)
      {
	float x(x_dist(rng));
	float y(y_dist(rng));
	float size(2.f * item.radius);

	auto clear(
	  not map_system.get_entity(x,        y,        floor).solid &&
	  not map_system.get_entity(x + size, y,        floor).solid &&
	  not map_system.get_entity(x,        y + size, floor).solid &&
	  not map_system.get_entity(x + size, y + size, floor).solid);

	if (clear)
	{
	  item.pos = {x, y};
	  map_system.get_chunk(x, y, floor).items.push_back(item);

	  break;
	}
      }
    }
  }
}


void EntitySystem::update()
{
  apply_user_inputs();

  if (input.activate) handle_activation();
}


void EntitySystem::apply_user_inputs()
{
  Vector2f direction(0, 0);

  if (input.left) direction.x() -= 1;
  if (input.right) direction.x() += 1;
  if (input.up) direction.y() -= 1;
  if (input.down) direction.y() += 1;

  if (direction.squaredNorm() != 0)
  {
    direction.normalize();
    active_user->vel = active_user->speed * direction;
  }
  else
    active_user->vel = Vector2f::Zero();
}


void EntitySystem::handle_activation()
{
  input.activate = false;

  Vector2f selection_point(camera_system.to_world_coordinates(input.mouse_pos));

  auto out_of_bounds(
    selection_point.x() < 0 || selection_point.x() >= MAP_SIZE_X ||
    selection_point.y() < 0 || selection_point.y() >= MAP_SIZE_Y);

  if (out_of_bounds) return;

  auto& entity(
    map_system.get_entity(selection_point.x(), selection_point.y(), active_user->floor));

  if (entity.type == "") return;

  auto sqrd_distance((entity.pos - active_user->pos).squaredNorm());

  if (sqrd_distance > 2.4f) return;

  if (entity.properties.door)
    handle_door(entity);
}


void EntitySystem::handle_door(Entity& entity)
{
  assert(entity.properties.door);

  Door& door(static_cast<Door&>(entity));

  cout << "Sparkys" << endl;

  map_system.open_door(door, !door.open);
}
