#pragma once

class Timer {
public:
  Timer();
  float getDT();

private:
  __int64 prev, freq;

};
