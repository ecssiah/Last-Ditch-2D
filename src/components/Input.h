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
      exit(false),
      activate(false)
  {}

  bool up, down;
  bool left, right;
  bool exit;
  bool activate;
};

}

#endif /* INPUT_H */
