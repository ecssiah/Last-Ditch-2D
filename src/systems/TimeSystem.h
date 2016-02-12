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

  double dt, game_time, game_time_rate;
  double game_minute_counter;
  int year, month, day;
  int hour, minute;

public:
  TimeSystem();

  double update();
  void tick();

  inline const int get_year() const { return year; }
  inline const int get_month() const { return month; }
  inline const int get_day() const { return day; }
  inline const int get_hour() const { return hour; }
  inline const int get_minute() const { return minute; }
};

}

#endif /* TIMESYSTEM_H */
