#ifndef PROPERTIES_H
#define PROPERTIES_H

namespace ld
{

struct Properties
{
  Properties()
    : door(false),
      item(false)
  {}

  bool door;
  bool item;
};

}

#endif /* PROPERTIES_H */
