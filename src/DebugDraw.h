#ifndef DEBUGDRAW_H
#define DEBUGDRAW_H

#include <Box2D/Box2D.h>
#include <iostream>
#include <SDL2/SDL.h>

#include "constants/MapConstants.h"
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
  }


  void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
  {
  }


  void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
  {
    SDL_SetRenderDrawColor(renderer, 200, 255, 255, 255);

    SDL_Rect rect;
    rect.x =
      TILE_SIZE * (vertices[0].x + .5 - camera_system.get_pos().x()) + SCREEN_SIZE_X / 2;
    rect.y =
      TILE_SIZE * (vertices[0].y + .5 - camera_system.get_pos().y()) + SCREEN_SIZE_Y / 2;
    rect.w = TILE_SIZE;
    rect.h = TILE_SIZE;

    SDL_RenderDrawRect(renderer, &rect);
  }


  void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {}

  void DrawSolidCircle(
    const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
  {
    SDL_SetRenderDrawColor(renderer, 200, 255, 255, 255);

    auto sides = 8;
    auto step = 2 * M_PI / sides;

    for (auto alpha = 0.0; alpha < 2 * M_PI; alpha += step)
    {
      auto x1 = center.x + .5 + radius * cos(alpha) - camera_system.get_pos().x();
      auto y1 = center.y + .5 + radius * sin(alpha) - camera_system.get_pos().y();
      auto x2 = center.x + .5 + radius * cos(alpha + step) - camera_system.get_pos().x();
      auto y2 = center.y + .5 + radius * sin(alpha + step) - camera_system.get_pos().y();

      SDL_RenderDrawLine(
	renderer,
	TILE_SIZE * x1 + SCREEN_SIZE_X / 2,
	TILE_SIZE * y1 + SCREEN_SIZE_Y / 2,
	TILE_SIZE * x2 + SCREEN_SIZE_X / 2,
	TILE_SIZE * y2 + SCREEN_SIZE_Y / 2);
    }
  }

  void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {}
  void DrawTransform(const b2Transform& xf) {}
};

#endif /* DEBUGDRAW_H */
