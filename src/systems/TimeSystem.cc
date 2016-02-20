#include "TimeSystem.h"

#include <iostream>

using namespace ld;
using namespace std;

TimeSystem::TimeSystem()
  : start(chrono::steady_clock::now()),
    end(start),
    dt(0.0),
    game_time_rate(62.f),
    game_time_tracker(0.0),
    game_minutes(0)
{
  auto year(3012), month(12), day(30);
  auto hour(23), minute(55);

  game_minutes =
    MINUTES_PER_YEAR * (year - BASE_YEAR) + MINUTES_PER_MONTH * (month - 1) +
    MINUTES_PER_DAY * (day - 1) + MINUTES_PER_HOUR * hour + minute;

  cout << endl << "TimeSystem ready" << endl;
}


double TimeSystem::update()
{
  end = chrono::steady_clock::now();
  auto microseconds(chrono::duration_cast<chrono::microseconds>(end - start).count());

  dt = microseconds / 1000.0;

  if (dt > .01) dt = .01;

  game_time_tracker += game_time_rate * dt;

  if (game_time_tracker >= 60.0)
  {
    ++game_minutes;
    game_time_tracker -= 60.0;
  }

  return dt;
}


void TimeSystem::tick()
{
  start = chrono::steady_clock::now();
}
