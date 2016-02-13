#ifndef DEBUGDRAW_H
#define DEBUGDRAW_H

#include <Box2D/Box2D.h>
#include <iostream>
#include <SDL2/SDL.h>

#include "constants/MapConstants.h"
#include "constants/RenderConstants.h"
#include "systems/CameraSystem.h"

using namespace ld;
using namespace std;

class DebugDraw : public b2Draw
{
  SDL_Renderer* renderer;

  CameraSystem& camera_system;

public:
  DebugDraw(SDL_Renderer* renderer_, CameraSystem& camera_system_)
    : renderer(renderer_),
      camera_system(camera_system_)
  {
    SetFlags(b2Draw::e_shapeBit);
  }


  void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
  {
  }


  void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
  {
    SDL_SetRenderDrawColor(renderer, 200, 255, 255, 255);

    auto center(vertices[0] + b2Vec2(.5, .5));

    SDL_Rect rect;
    rect.x = PIXELS_PER_UNIT * (center.x - camera_system.get_pos().x()) + HALF_SCREEN_SIZE_X;
    rect.y = PIXELS_PER_UNIT * (center.y - camera_system.get_pos().y()) + HALF_SCREEN_SIZE_Y;
    rect.w = PIXELS_PER_UNIT;
    rect.h = PIXELS_PER_UNIT;

    SDL_RenderDrawRect(renderer, &rect);
  }


  void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {}

  void DrawSolidCircle(
    const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
  {
    SDL_SetRenderDrawColor(renderer, 200, 255, 255, 255);

    auto sides(16);
    auto step(2 * M_PI / sides);

    for (auto alpha(0.0); alpha < 2 * M_PI; alpha += step)
    {
      auto x1(center.x + .5 + radius * cos(alpha) - camera_system.get_pos().x());
      auto y1(center.y + .5 + radius * sin(alpha) - camera_system.get_pos().y());
      auto x2(center.x + .5 + radius * cos(alpha + step) - camera_system.get_pos().x());
      auto y2(center.y + .5 + radius * sin(alpha + step) - camera_system.get_pos().y());

      SDL_RenderDrawLine(
	renderer,
	PIXELS_PER_UNIT * x1 + HALF_SCREEN_SIZE_X,
	PIXELS_PER_UNIT * y1 + HALF_SCREEN_SIZE_Y,
	PIXELS_PER_UNIT * x2 + HALF_SCREEN_SIZE_X,
	PIXELS_PER_UNIT * y2 + HALF_SCREEN_SIZE_Y);
    }
  }

  void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {}
  void DrawTransform(const b2Transform& xf) {}
};

#endif /* DEBUGDRAW_H */
