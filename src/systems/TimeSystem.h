#ifndef TIMESYSTEM_H
#define TIMESYSTEM_H

#include <chrono>
#include <cmath>
#include <string>

#include "../components/Input.h"
#include "../constants/SimulationConstants.h"

namespace ld
{

constexpr double MAX_DELTA_TIME(.2);

class TimeSystem
{
  std::chrono::steady_clock::time_point start;
  std::chrono::steady_clock::time_point end;

  Input& input;

  unsigned long long game_minutes;

  double dt;
  double game_minute_tracker;

public:
  TimeSystem(Input& input);

  double update();
  void tick();

  std::string get_string() const;

  inline const int get_minute() const;
  inline const int get_hour() const;
  inline const int get_day() const;
  inline const int get_month() const;
  inline const int get_year() const;
};

const int TimeSystem::get_minute() const
{
  return game_minutes % MINUTES_PER_HOUR;
}

const int TimeSystem::get_hour() const
{
  return game_minutes / MINUTES_PER_HOUR % HOURS_PER_DAY;
}

const int TimeSystem::get_day() const
{
  return 1 + (game_minutes / MINUTES_PER_DAY) % DAYS_PER_MONTH;
}

const int TimeSystem::get_month() const
{
  return 1 + (game_minutes / MINUTES_PER_MONTH) % MONTHS_PER_YEAR;
}

const int TimeSystem::get_year() const
{
  return BASE_YEAR + game_minutes / MINUTES_PER_YEAR;
}

}

#endif /* TIMESYSTEM_H */
