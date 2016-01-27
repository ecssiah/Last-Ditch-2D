#include "TimeSystem.h"

#include <iostream>

using namespace ld;
using namespace std;

TimeSystem::TimeSystem()
  : start(chrono::steady_clock::now()),
    end(chrono::steady_clock::now())
{
  cout << endl << "Time system ready" << endl;
}


double TimeSystem::update()
{
  end = chrono::steady_clock::now();
  auto microseconds = chrono::duration_cast<chrono::microseconds>(end - start).count();

  return microseconds / 100.0;
}


void TimeSystem::tick()
{
  start = chrono::steady_clock::now();
}
