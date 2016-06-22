#pragma once

//A simple timer class, using high-frequency timer
//getDT() function returns seconds elapsed since last time it was called

class Timer {
public:
  Timer();
  float getDT();

private:
  __int64 prev, freq;

};
