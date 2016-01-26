#ifndef ROOM_H
#define ROOM_H

namespace ld
{

struct Room
{
  Room(int x_, int y_, int w_, int h_, int floor_)
    : x(x_),
      y(y_),
      w(w_),
      h(h_),
      floor(floor_)
  {}

  int x, y;
  int w, h;
  int floor;
};

}

#endif /* ROOM_H */
