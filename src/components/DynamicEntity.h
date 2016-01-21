#ifndef DYNAMICENTITY_H
#define DYNAMICENTITY_H

#include <string>

namespace ld
{

struct DynamicEntity
{
  DynamicEntity()
    : name(""),
      type("")
  {}

  std::string name, type;
};

}

#endif /* DYNAMICENTITY_H */
