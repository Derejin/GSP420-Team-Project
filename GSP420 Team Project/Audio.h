#pragma once
#include <string>
#include "Sound.h"
#include "Song.h"

//An Audio object must exist for the Song and Sound classes to function.
//No further interaction with this class should be required.

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
