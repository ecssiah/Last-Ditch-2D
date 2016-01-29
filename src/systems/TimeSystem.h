#ifndef TIMESYSTEM_H
#define TIMESYSTEM_H

#include <chrono>

namespace ld
{

class TimeSystem
{
  void update_game_time();

  std::chrono::steady_clock::time_point start;
  std::chrono::steady_clock::time_point end;

  double dt, game_minute_counter, game_time, game_time_rate;
  int year, month, day;
  int hour, minute;

public:
  TimeSystem();

  double update();
  void tick();

  const int get_year() const { return year; }
  const int get_month() const { return month; }
  const int get_day() const { return day; }
  const int get_hour() const { return hour; }
  const int get_minute() const { return minute; }
};

}

#endif /* TIMESYSTEM_H */
