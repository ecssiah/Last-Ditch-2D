#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Item.h"

namespace ld
{

struct Equipment
{
  Equipment()
    : head(nullptr),
      shoulders(nullptr),
      chest(nullptr),
      back(nullptr),
      waist(nullptr),
      l_arm(nullptr),
      r_arm(nullptr),
      l_hand(nullptr),
      r_hand(nullptr),
      l_leg(nullptr),
      r_leg(nullptr),
      l_foot(nullptr),
      r_foot(nullptr)
  {}

  Item* head;
  Item* shoulders;
  Item* chest;
  Item* back;
  Item* waist;
  Item* l_arm;
  Item* r_arm;
  Item* l_hand;
  Item* r_hand;
  Item* l_leg;
  Item* r_leg;
  Item* l_foot;
  Item* r_foot;
};

}

#endif /* EQUIPMENT_H */
