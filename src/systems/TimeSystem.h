#ifndef TIMESYSTEM_H
#define TIMESYSTEM_H

#include <chrono>
#include <cmath>

#include "../constants/SimulationConstants.h"

namespace ld
{

class TimeSystem
{
  std::chrono::steady_clock::time_point start;
  std::chrono::steady_clock::time_point end;

  double dt;
  double game_time_rate, game_time_tracker;

  int game_minutes;

public:
  TimeSystem();

  double update();
  void tick();

  inline const int get_year() const;
  inline const int get_month() const;
  inline const int get_day() const;
  inline const int get_hour() const;
  inline const int get_minute() const;
};

const int TimeSystem::get_year() const
{
  return game_minutes / MINUTES_PER_YEAR;
}

const int TimeSystem::get_month() const
{
  return game_minutes / MINUTES_PER_MONTH;
}

const int TimeSystem::get_day() const
{
  return (game_minutes % MINUTES_PER_MONTH) / MINUTES_PER_DAY;
}

const int TimeSystem::get_hour() const
{
  return (game_minutes % MINUTES_PER_DAY) / MINUTES_PER_HOUR;
}

const int TimeSystem::get_minute() const
{
  return game_minutes % MINUTES_PER_HOUR;
}

}

#endif /* TIMESYSTEM_H */
