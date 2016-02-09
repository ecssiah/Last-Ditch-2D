#include "EntitySystem.h"

#include <eigen3/Eigen/Geometry>
#include <iostream>
#include <random>

#include "../components/Item.h"
#include "../constants/ItemConstants.h"
#include "../constants/MapConstants.h"
#include "../constants/RenderConstants.h"

using namespace ld;
using namespace Eigen;
using namespace std;

EntitySystem::EntitySystem(mt19937& rng_, Input& input_, MapSystem& map_system_)
  : rng(rng_),
    input(input_),
    map_system(map_system_),
    active_user(nullptr),
    users()
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
  kadijah.pos = {1, 2};
  kadijah.floor = 0;
  kadijah.radius = .48;
  kadijah.speed = 240;
  kadijah.clip_rect.w = PIXELS_PER_UNIT;
  kadijah.clip_rect.h = PIXELS_PER_UNIT;

  users.push_back(kadijah);
  active_user = &users.back();
}


std::string EntitySystem::get_random_type()
{
  uniform_int_distribution<> type_choice(0, ITEM_TYPES.size() - 1);

  return ITEM_TYPES[type_choice(rng)];
}


void EntitySystem::setup_items()
{
  for (auto i = 0; i < NUM_ITEMS; ++i)
  {
    uniform_real_distribution<> x_position_choice(0, MAP_SIZE_X - 1);
    uniform_real_distribution<> y_position_choice(0, MAP_SIZE_Y - 1);

    Item item;
    item.type = get_random_type();

    while (1)
    {
      float x(x_position_choice(rng));
      float y(y_position_choice(rng));
      float size(2.f * item.radius);

      auto clear(
	!map_system.get_entity(x,        y,        0).solid &&
	!map_system.get_entity(x + size, y,        0).solid &&
	!map_system.get_entity(x,        y + size, 0).solid &&
	!map_system.get_entity(x + size, y + size, 0).solid);

      if (clear)
      {
	item.pos = {x, y};
	map_system.get_chunk(x, y, 0).items.push_back(item);

	break;
      }
    }
  }
}


void EntitySystem::update()
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

  if (input.activate)
  {
    input.activate = false;

    Vector2f pos_center(active_user->pos.x(), active_user->pos.y() + .5f);

    auto& chunk(
      map_system.get_chunk(pos_center.x(), pos_center.y(), active_user->floor));
  }
}
