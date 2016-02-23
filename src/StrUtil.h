#ifndef STRUTIL_H
#define STRUTIL_H

#include <string>

namespace StrUtil
{

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


#endif /* STRUTIL_H */
