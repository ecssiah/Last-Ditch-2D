#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

#include "components/ui/Element.h"

namespace Utils
{

float clamp(float value, float lower_bound, float upper_bound);

bool ends_with(const std::string& string, const std::string& suffix);

bool point_intersects_element(Eigen::Vector2i point, ld::Element& element);

void print_rect(SDL_Rect& rect);

}


#endif /* UTILS_H */
