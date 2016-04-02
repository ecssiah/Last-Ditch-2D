#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>

#include "../SDL_Interface.h"
#include "../constants/MapConstants.h"
#include "../constants/RenderConstants.h"
#include "../components/Entity.h"

namespace ld
{

class CameraSystem
{
  Eigen::Vector2f pos;

  Entity* target;

  SDL_Interface& sdl_interface;

public:
  CameraSystem(SDL_Interface& sdl_interface);

  void update();

  inline Eigen::Vector2f get_pos() { return pos; }
  inline void set_target(Entity* target_) { target = target_; }

  inline Eigen::Vector2f to_world_coordinates(Eigen::Vector2i screen_pos_pixels);
};


Eigen::Vector2f CameraSystem::to_world_coordinates(Eigen::Vector2i screen_pos_pixels)
{
  Eigen::Vector2f screen_pos(
    screen_pos_pixels.x() / (float)PIXELS_PER_UNIT,
    screen_pos_pixels.y() / (float)PIXELS_PER_UNIT);

  Eigen::Vector2f world_pos(
    screen_pos.x() + pos.x() - HALF_SCREEN_SIZE_X_WORLD,
    screen_pos.y() + pos.y() - HALF_SCREEN_SIZE_Y_WORLD);

  return world_pos;
}


}


#endif /* CAMERASYSTEM_H */
