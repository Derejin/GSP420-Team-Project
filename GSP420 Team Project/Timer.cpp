#include "Timer.h"
#include <Windows.h>

Timer::Timer() {
  QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
  QueryPerformanceCounter((LARGE_INTEGER*)&prev);
}

float Timer::getDT() {
  __int64 now;
  QueryPerformanceCounter((LARGE_INTEGER*)&now);

  float seconds = float(now - prev) / freq;

  prev = now;

  return seconds;
}
