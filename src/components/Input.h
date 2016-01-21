#ifndef INPUT_H
#define INPUT_H

namespace ld
{

struct Input
{
  Input()
    : up(false),
      down(false),
      left(false),
      right(false),
      exit(false)
  {}

  bool up, down;
  bool left, right;
  bool exit;
};

}

#endif /* INPUT_H */
