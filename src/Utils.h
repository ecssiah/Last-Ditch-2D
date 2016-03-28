#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace Utils
{

float clamp(float value, float lower_bound, float upper_bound);

bool ends_with(const std::string& string, const std::string& suffix);

}


#endif /* UTILS_H */
