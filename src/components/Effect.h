#ifndef EFFECT_H
#define EFFECT_H

#include <string>

namespace ld
{

struct Effect
{
  Effect() = default;

  std::string type;
  float value;
  unsigned duration;
};

}

#endif /* EFFECT_H */
