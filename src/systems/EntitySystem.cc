#include "EntitySystem.h"

#include <algorithm>
#include <eigen3/Eigen/Geometry>
#include <iostream>
#include <random>

#include "../Utils.h"
#include "../components/Door.h"
#include "../components/Item.h"
#include "../constants/ItemConstants.h"
#include "../constants/MapConstants.h"
#include "../constants/RenderConstants.h"
#include "../constants/UserConstants.h"

using namespace Eigen;
using namespace std;
using namespace Utils;

namespace ld
{

EntitySystem::EntitySystem(
  mt19937& _rng,
  Input& _input,
  vector<User>& _users,
  CameraSystem& _camera_system, MapSystem& _map_system
)
  : rng(_rng),
    input(_input),
    users(_users),
    map_system(_map_system),
    camera_system(_camera_system)
{
  setup_items();
  setup_users();

  printf("EntitySystem ready\n");
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
      item.floor = floor;
      item.type = get_random_item_type();
      item.texture = Item_Data[item.type].texture;
      item.name = Item_Data[item.type].name;
      item.category = Item_Data[item.type].category;
      item.value = Item_Data[item.type].value;
      item.quality = Item_Data[item.type].quality;
      item.weight = Item_Data[item.type].weight;
      item.volume = Item_Data[item.type].volume;

      for (auto i(0); i < 1000; ++i)
      {
	float x(x_dist(rng));
	float y(y_dist(rng));
	float size_x(item.size.x());
	float size_y(item.size.y());

	auto clear(
	  !map_system.get_main_tile(x, y, floor).solid &&
	  !map_system.get_main_tile(x + size_x, y, floor).solid &&
	  !map_system.get_main_tile(x, y + size_y, floor).solid &&
	  !map_system.get_main_tile(x + size_x, y + size_y, floor).solid);

	if (clear)
	{
	  item.pos = {x, y};
	  map_system.get_chunk(
	    x / TILES_PER_CHUNK_X, y / TILES_PER_CHUNK_Y, floor).items.push_back(item);

	  break;
	}
      }
    }
  }
}


void EntitySystem::setup_users()
{
  User user;
  user.name = "Kadijah";
  user.type = "kadijah";
  user.texture = "kadijah";
  user.animation = "idle-front";
  user.floor = 0;
  user.speed = 50.f;
  user.pos = {3.f, 9.f};
  user.size = {.48f, .48f};
  user.clip_rect = User_Data[user.type].animation_data[user.animation].clip_rect;

  for (auto i(0); i < 10; ++i) give_random_item(user);

  users.push_back(user);
}


void EntitySystem::update()
{
  apply_user_inputs();

  update_users();

  if (input.activate) handle_activation();
}


void EntitySystem::apply_user_inputs()
{
  Vector2f direction(0, 0);
  auto& animation(users[0].animation);

  if (input.left) direction.x() -= 1;
  if (input.right) direction.x() += 1;
  if (input.up) direction.y() -= 1;
  if (input.down) direction.y() += 1;

  if (direction.squaredNorm() == 0)
  {
    users[0].vel = Vector2f::Zero();

    if (animation == "walk-front") animation = "idle-front";
    else if (animation == "walk-back") animation = "idle-back";
    else if (animation == "walk-left") animation = "idle-left";
    else if (animation == "walk-right") animation = "idle-right";
  }
  else
  {
    direction.normalize();
    auto vel(users[0].speed * direction);

    if (vel.x() > 0) animation = "walk-right";
    else if (vel.x() < 0) animation = "walk-left";
    else if (vel.y() > 0) animation = "walk-front";
    else if (vel.y() < 0) animation = "walk-back";

    users[0].vel = vel;
  }
}


void EntitySystem::update_users()
{


}


void EntitySystem::handle_activation()
{
  Vector2f selection_point(
    camera_system.to_world_coordinates(input.left_mouse_released_pos));

  auto out_of_bounds(
    selection_point.x() < 0 || selection_point.x() >= MAP_SIZE_X ||
    selection_point.y() < 0 || selection_point.y() >= MAP_SIZE_Y);

  if (out_of_bounds) return;

  auto& chunk(
    map_system.get_chunk(selection_point.x(), selection_point.y(), users[0].floor));

  if (find_and_interact_door(selection_point, chunk))
  {
    input.activate = false;
    return;
  }

  if (find_and_interact_item(selection_point, chunk))
  {
    input.activate = false;
    users[0].inventory.modified = true;
    return;
  }
}


void EntitySystem::give_random_item(User& user)
{
  Item item;
  item.type = get_random_item_type();
  item.texture = Item_Data[item.type].texture;
  item.name = Item_Data[item.type].name;
  item.category = Item_Data[item.type].category;
  item.value = Item_Data[item.type].value;
  item.quality = Item_Data[item.type].quality;
  item.weight = Item_Data[item.type].weight;
  item.volume = Item_Data[item.type].volume;

  user.inventory.items.push_back(item);
}


std::string EntitySystem::get_random_item_type()
{
  auto item_types(Item_Types);
  std::random_shuffle(item_types.begin(), item_types.end());

  return item_types[0];
}


bool EntitySystem::find_and_interact_door(Vector2f& selection_point, Chunk& chunk)
{
  for (auto& door : chunk.doors)
  {
    auto hit(
      selection_point.x() > door.pos.x() && selection_point.x() < door.pos.x() + 1 &&
      selection_point.y() > door.pos.y() && selection_point.y() < door.pos.y() + 1);

    if (!hit) continue;

    auto user_center(users[0].pos + Vector2f(.5, .5));
    auto in_range((user_center - selection_point).squaredNorm() < 2.7f);

    if (!in_range) continue;

    map_system.use_door(door);

    return true;
  }

  return false;
}


bool EntitySystem::find_and_interact_item(Vector2f& selection_point, Chunk& chunk)
{
  auto& items(chunk.items);

  for (auto it(items.begin()); it != items.end(); ++it)
  {
    auto& item(*it);

    auto hit(
      selection_point.x() > item.pos.x() &&
      selection_point.x() < item.pos.x() + item.size.x() &&
      selection_point.y() > item.pos.y() &&
      selection_point.y() < item.pos.y() + item.size.y());

    if (!hit) continue;

    auto user_center(users[0].pos + Vector2f(.5, .5));
    auto in_range((user_center - selection_point).squaredNorm() < 2.7f);

    if (!in_range) continue;

    item.contained = true;
    users[0].inventory.items.push_back(item);

    items.erase(it);

    return true;
  }

  return false;
}

}
