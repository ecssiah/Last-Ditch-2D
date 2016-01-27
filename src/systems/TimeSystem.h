#ifndef TIMESYSTEM_H
#define TIMESYSTEM_H

#include <chrono>

namespace ld
{

class TimeSystem
{
  std::chrono::steady_clock::time_point start;
  std::chrono::steady_clock::time_point end;

public:
  TimeSystem();

  double update();
  void tick();
};

}

#endif /* TIMESYSTEM_H */
