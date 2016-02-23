#ifndef ANIMATIONDATA_H
#define ANIMATIONDATA_H

namespace ld
{

struct AnimationData
{
  AnimationData()
    : x(0),
      y(0),
      frames(0)
  {}

  AnimationData(int _x, int _y, int _frames)
    : x(_x),
      y(_y),
      frames(_frames)
  {}

  int x, y;
  int frames;
};

}


#endif /* ANIMATIONDATA_H */
