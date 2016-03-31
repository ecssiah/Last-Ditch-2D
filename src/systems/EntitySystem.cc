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
#include "../constants/UserConstants.h"

using namespace ld;
using namespace Eigen;
using namespace std;

EntitySystem::EntitySystem(
  mt19937& _rng, Input& _input, CameraSystem& _camera_system, MapSystem& _map_system
)
  : rng(_rng),
    input(_input),
    map_system(_map_system),
    camera_system(_camera_system),
    active_user(nullptr),
    users(NUM_FLOORS),
    item_types()
{
  setup_users();
  setup_items();

  cout << "EntitySystem ready" << endl;
}


void EntitySystem::setup_users()
{
  User kadijah;
  kadijah.name = "Kadijah";
  kadijah.type = "kadijah";
  kadijah.pos = {3, 9};
  kadijah.floor = 0;
  kadijah.radius = .48f;
  kadijah.speed = 50.f;

  kadijah.texture = USER_INFO[kadijah.type].texture;
  kadijah.animation = "body-idle-front";
  kadijah.clip_rect.x = USER_INFO[kadijah.type].anim_data[kadijah.animation].clip_x;
  kadijah.clip_rect.y = USER_INFO[kadijah.type].anim_data[kadijah.animation].clip_y;

  kadijah.arm_texture = USER_INFO[kadijah.type].texture;
  kadijah.arm_animation = "arm-idle-nequip-front";
  kadijah.arm_clip_rect.x = USER_INFO[kadijah.type].anim_data[kadijah.arm_animation].clip_x;
  kadijah.arm_clip_rect.y = USER_INFO[kadijah.type].anim_data[kadijah.arm_animation].clip_y;

  users[kadijah.floor].push_back(kadijah);
  active_user = &users[kadijah.floor].back();

  for (auto i(0); i < 10; ++i) give_random_item(active_user);
}


void EntitySystem::give_random_item(User* user)
{
  Item item;
  item.type = get_random_type();
  item.texture = ITEM_INFO[item.type].texture;
  item.name = ITEM_INFO[item.type].name;
  item.category = ITEM_INFO[item.type].category;
  item.value = ITEM_INFO[item.type].value;
  item.quality = ITEM_INFO[item.type].quality;
  item.weight = ITEM_INFO[item.type].weight;
  item.volume = ITEM_INFO[item.type].volume;

  user->inventory.items.push_back(item);
}


std::string EntitySystem::get_random_type()
{
  uniform_int_distribution<> type_dist(0, ITEM_INFO.size() - 1);

  auto it(std::next(std::begin(ITEM_INFO), type_dist(rng)));
  auto random_type((*it).first);

  return random_type;
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
      item.type = get_random_type();
      item.texture = ITEM_INFO[item.type].texture;
      item.name = ITEM_INFO[item.type].name;
      item.category = ITEM_INFO[item.type].category;
      item.value = ITEM_INFO[item.type].value;
      item.quality = ITEM_INFO[item.type].quality;
      item.weight = ITEM_INFO[item.type].weight;
      item.volume = ITEM_INFO[item.type].volume;

      while (1)
      {
	float x(x_dist(rng));
	float y(y_dist(rng));
	float size(2.f * item.radius);

	auto clear(
	  !map_system.get_main_tile(x,        y,        floor).solid &&
	  !map_system.get_main_tile(x + size, y,        floor).solid &&
	  !map_system.get_main_tile(x,        y + size, floor).solid &&
	  !map_system.get_main_tile(x + size, y + size, floor).solid);

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

  auto& animation(active_user->animation);
  string new_animation(animation);

  if (direction.squaredNorm() == 0)
  {
    active_user->vel = Vector2f::Zero();

    if (animation == "body-walk-front")
      animation = "body-idle-front";
    else if (animation == "body-walk-back")
      animation = "body-idle-back";
    else if (animation == "body-walk-left")
      animation = "body-idle-left";
    else if (animation == "body-walk-right")
      animation = "body-idle-right";
  }
  else
  {
    direction.normalize();
    auto vel(active_user->speed * direction);

    if (vel.x() > 0)
      animation = "body-walk-right";
    else if (vel.x() < 0)
      animation = "body-walk-left";
    else if (vel.y() > 0)
      animation = "body-walk-front";
    else if (vel.y() < 0)
      animation = "body-walk-back";

    active_user->vel = vel;
  }

  auto& arm_animation(active_user->arm_animation);
  string new_arm_animation(arm_animation);

  if (direction.squaredNorm() == 0)
  {
    active_user->vel = Vector2f::Zero();

    if (arm_animation == "arm-walk-nequip-front")
      arm_animation = "arm-idle-nequip-front";
    else if (arm_animation == "arm-walk-nequip-back")
      arm_animation = "arm-idle-nequip-back";
    else if (arm_animation == "arm-walk-nequip-left")
      arm_animation = "arm-idle-nequip-left";
    else if (arm_animation == "arm-walk-nequip-right")
      arm_animation = "arm-idle-nequip-right";
  }
  else
  {
    direction.normalize();
    auto vel(active_user->speed * direction);

    if (vel.x() > 0)
      arm_animation = "arm-walk-nequip-right";
    else if (vel.x() < 0)
      arm_animation = "arm-walk-nequip-left";
    else if (vel.y() > 0)
      arm_animation = "arm-walk-nequip-front";
    else if (vel.y() < 0)
      arm_animation = "arm-walk-nequip-back";

    active_user->vel = vel;
  }
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
    map_system.get_chunk(selection_point.x(), selection_point.y(), active_user->floor));

  if (find_and_interact_door(selection_point, chunk))
  {
    input.activate = false;
    return;
  }

  if (find_and_interact_item(selection_point, chunk))
  {
    input.activate = false;
    active_user->inventory.modified = true;
    return;
  }
}


bool EntitySystem::find_and_interact_door(Vector2f& selection_point, Chunk& chunk)
{
  for (auto& door : chunk.doors)
  {
    auto hit(
      selection_point.x() > door.pos.x() && selection_point.x() < door.pos.x() + 1 &&
      selection_point.y() > door.pos.y() && selection_point.y() < door.pos.y() + 1);

    if (!hit) continue;

    auto user_center(active_user->pos + Vector2f(.5, .5));
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
      selection_point.x() < item.pos.x() + item.radius &&
      selection_point.y() > item.pos.y() &&
      selection_point.y() < item.pos.y() + item.radius);

    if (!hit) continue;

    auto user_center(active_user->pos + Vector2f(.5, .5));
    auto in_range((user_center - selection_point).squaredNorm() < 2.7f);

    if (!in_range) continue;

    item.contained = true;
    active_user->inventory.items.push_back(item);

    items.erase(it);

    return true;
  }

  return false;
}
