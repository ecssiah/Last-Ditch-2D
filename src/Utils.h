#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <string>

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

}


#endif /* UTILS_H */
