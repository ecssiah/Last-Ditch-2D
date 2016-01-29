#include "TimeSystem.h"

#include <iostream>

using namespace ld;
using namespace std;

TimeSystem::TimeSystem()
  : start(chrono::steady_clock::now()),
    end(chrono::steady_clock::now()),
    dt(0.0),
    game_minute_counter(0.0),
    game_time(0.0),
    game_time_rate(2.1),
    year(3212),
    month(1),
    day(28),
    hour(11),
    minute(10)
{
  cout << endl << "Time system ready" << endl;
}


double TimeSystem::update()
{
  end = chrono::steady_clock::now();
  auto microseconds = chrono::duration_cast<chrono::microseconds>(end - start).count();

  dt = microseconds / 1000.0;
  game_time += dt * game_time_rate;
  game_minute_counter += dt * game_time_rate;

  update_game_time();

  return dt;
}


void TimeSystem::tick()
{
  start = chrono::steady_clock::now();
}


void TimeSystem::update_game_time()
{
  if (game_minute_counter >= 60.0)
  {
    ++minute;
    game_minute_counter -= 60.0;

    if (minute > 59)
    {
      ++hour;
      minute = 0;

      if (hour > 23)
      {
	++day;
	hour = 0;

	if (day > 30)
	{
	  ++month;
	  day = 1;

	  if (month > 12)
	  {
	    ++year;
	    month = 1;
	  }
	}
      }
    }
  }
}
