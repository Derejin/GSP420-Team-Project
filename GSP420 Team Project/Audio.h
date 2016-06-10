#pragma once
#include <string>
#include "Sound.h"

namespace FMOD {
  class System;
}

class Audio {
public:
  Audio();
  ~Audio();
  Sound createSound(const std::string& filename);

private:
  static const int MAX_CHANNELS = 512;
  FMOD::System* system = nullptr;

};
