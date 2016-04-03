#ifndef DAMAGE_H
#define DAMAGE_H

namespace ld
{

struct Damage
{
  Damage() = default;

  float physical;
  float energy;
  float heat;
  float cold;
};

}

#endif /* DAMAGE_H */
