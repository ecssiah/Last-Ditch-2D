#include "TimeSystem.h"

#include <algorithm>
#include <iostream>
#include <sstream>

using namespace ld;
using namespace std;

TimeSystem::TimeSystem(Input& _input)
  : start(chrono::steady_clock::now()),
    end(start),
    input(_input),
    game_minutes(0),
    dt(0.0),
    game_minute_tracker(0.0)
{
  auto year(2484), month(12), day(30);
  auto hour(23), minute(55);

  game_minutes =
    (year - BASE_YEAR) * MINUTES_PER_YEAR +
    (month - 1) * MINUTES_PER_MONTH +
    (day - 1) * MINUTES_PER_DAY +
    hour * MINUTES_PER_HOUR +
    minute;

  printf("TimeSystem ready\n");
}


double TimeSystem::update()
{
  end = chrono::steady_clock::now();
  auto microseconds(chrono::duration_cast<chrono::microseconds>(end - start).count());

  dt = std::min(MAX_DELTA_TIME, 1e-6 * microseconds);

  if (!input.pause)
  {
    game_minute_tracker += dt;

    if (game_minute_tracker >= LENGTH_OF_GAME_MINUTE)
    {
      ++game_minutes;
      game_minute_tracker -= LENGTH_OF_GAME_MINUTE;
    }
  }

  return dt;
}


void TimeSystem::tick()
{
  start = chrono::steady_clock::now();
}


string TimeSystem::get_string() const
{
  stringstream ss;

  auto minute(get_minute());
  auto hour(get_hour());

  hour < 10 ? ss << "0" << hour : ss << hour;
  ss << ":";
  minute < 10 ? ss << "0" << minute : ss << minute;

  auto day(get_day());
  auto month(get_month());

  ss << " ";
  day < 10 ? ss << "0" << day : ss << day;
  ss << "/";
  month < 10 ? ss << "0" << month : ss << month;
  ss << "/" << get_year();

  return ss.str();
}
