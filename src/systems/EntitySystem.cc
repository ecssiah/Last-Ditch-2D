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
    inventory_system(),
    active_user(nullptr),
    users(NUM_FLOORS),
    frame_time(0.0),
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
  kadijah.radius = .48;
  kadijah.speed = 240;

  kadijah.body_texture = TYPE_TO_TEXTURE[kadijah.type];
  kadijah.body_animation = "idle-front";
  kadijah.body_clip_rect.x =
    PIXELS_PER_UNIT * ANIMATION_DATA[kadijah.type][kadijah.body_animation].x;
  kadijah.body_clip_rect.y =
    PIXELS_PER_UNIT * ANIMATION_DATA[kadijah.type][kadijah.body_animation].y;

  kadijah.arm_texture = TYPE_TO_TEXTURE[kadijah.type];
  kadijah.arm_animation = "idle-front";
  kadijah.arm_clip_rect.x =
    PIXELS_PER_UNIT * ANIMATION_DATA[kadijah.type][kadijah.arm_animation].x;
  kadijah.arm_clip_rect.y =
    PIXELS_PER_UNIT * ANIMATION_DATA[kadijah.type][kadijah.arm_animation].y;

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
      item.floor = floor;

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


void EntitySystem::update(double dt)
{
  apply_user_inputs();
  update_animations(dt);
  if (input.activate) handle_activation();
}


void EntitySystem::update_animations(double& dt)
{
  frame_time += dt;

  if (frame_time > .03)
  {
    frame_time = 0.0;

    for (auto& user : users[active_user->floor])
    {
      const auto& body_anim_data(ANIMATION_DATA[user.type][user.body_animation]);

      if (user.frame < body_anim_data.frames - 1)
	++user.frame;
      else
	user.frame = 0;

      auto body_x(body_anim_data.x + user.frame);
      auto body_y(body_anim_data.y);

      user.body_clip_rect.x = PIXELS_PER_UNIT * body_x;
      user.body_clip_rect.y = PIXELS_PER_UNIT * body_y;

      const auto& arm_anim_data(ANIMATION_DATA[user.type][user.arm_animation]);

      if (user.frame < arm_anim_data.frames - 1)
	++user.frame;
      else
	user.frame = 0;

      auto arm_x(arm_anim_data.x + user.frame);
      auto arm_y(arm_anim_data.y);

      user.arm_clip_rect.x = PIXELS_PER_UNIT * arm_x;
      user.arm_clip_rect.y = PIXELS_PER_UNIT * arm_y;
    }
  }
}


void EntitySystem::apply_user_inputs()
{
  Vector2f direction(0, 0);

  if (input.left) direction.x() -= 1;
  if (input.right) direction.x() += 1;
  if (input.up) direction.y() -= 1;
  if (input.down) direction.y() += 1;

  auto& body_animation(active_user->body_animation);
  string new_body_animation(body_animation);

  if (direction.squaredNorm() == 0)
  {
    active_user->vel = Vector2f::Zero();

    if (body_animation == "body-walk-front")
      body_animation = "body-idle-front";
    else if (body_animation == "body-walk-back")
      body_animation = "body-idle-back";
    else if (body_animation == "body-walk-left")
      body_animation = "body-idle-left";
    else if (body_animation == "body-walk-right")
      body_animation = "body-idle-right";
  }
  else
  {
    direction.normalize();
    auto vel(active_user->speed * direction);

    if (vel.x() > 0)
      body_animation = "body-walk-right";
    else if (vel.x() < 0)
      body_animation = "body-walk-left";
    else if (vel.y() > 0)
      body_animation = "body-walk-front";
    else if (vel.y() < 0)
      body_animation = "body-walk-back";

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
  input.activate = false;

  Vector2f selection_point(camera_system.to_world_coordinates(input.mouse_pos));

  auto out_of_bounds(
    selection_point.x() < 0 || selection_point.x() >= MAP_SIZE_X ||
    selection_point.y() < 0 || selection_point.y() >= MAP_SIZE_Y);

  if (out_of_bounds) return;

  auto& chunk(
    map_system.get_chunk(selection_point.x(), selection_point.y(), active_user->floor));

  if (find_and_interact_door(selection_point, chunk)) return;
  if (find_and_interact_item(selection_point, chunk)) return;
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

    map_system.open_door(door);

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
