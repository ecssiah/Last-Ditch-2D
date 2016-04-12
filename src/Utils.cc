#include "Utils.h"

#include <algorithm>
#include <eigen3/Eigen/Geometry>

#include "components/ui/Element.h"

using namespace Eigen;

namespace Utils
{

float clamp(float value, float lower_bound, float upper_bound)
{
  return std::max(lower_bound, std::min(value, upper_bound));
}


bool ends_with(const std::string& string, const std::string& suffix)
{
  if (string.length() >= suffix.length())
  {
    auto found(string.compare(string.length() - suffix.length(), suffix.length(), suffix));

    if (found) return true;
  }

  return false;
}


bool point_intersects_element(Vector2i point, ld::Element& element)
{
  auto hit(
    point.x() >= element.dest_rect.x &&
    point.x() < element.dest_rect.x + element.dest_rect.w &&
    point.y() >= element.dest_rect.y &&
    point.y() < element.dest_rect.y + element.dest_rect.h);

  return hit;
}


bool rect_intersects_rect(SDL_Rect& rect1, SDL_Rect& rect2)
{
  auto outside(
    rect1.x > rect2.x + rect2.w ||
    rect1.x + rect1.w < rect2.x ||
    rect1.y > rect2.y + rect2.h ||
    rect1.y + rect1.h < rect2.y);

  auto hit(!outside);

  return hit;
}


void print_rect(SDL_Rect& rect)
{
  printf("%d %d %d %d\n", rect.x, rect.y, rect.w, rect.h);
}

}
