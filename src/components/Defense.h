#ifndef DEFENSE_H
#define DEFENSE_H

namespace ld
{

struct Defense
{
  Defense() = default;

  float physical;
  float energy;
  float heat;
  float cold;
};

}

#endif /* DEFENSE_H */
