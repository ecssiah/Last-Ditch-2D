#ifndef ANIMATIONDATA_H
#define ANIMATIONDATA_H

namespace ld
{

struct AnimationData
{
  AnimationData() = default;

  AnimationData(unsigned _clip_x, unsigned _clip_y, unsigned _num_frames)
    : clip_x(_clip_x),
      clip_y(_clip_y),
      num_frames(_num_frames)
    {}

  unsigned clip_x, clip_y;
  unsigned num_frames;
};

}

#endif /* ANIMATIONDATA_H */
