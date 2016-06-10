#pragma once
#include <string>
#include "Sound.h"
#include "Song.h"

namespace FMOD {
  class System;
}

class Audio {
public:
  Audio();
  ~Audio();

private:
  static const int MAX_CHANNELS = 512;
  FMOD::System* system = nullptr;

};
