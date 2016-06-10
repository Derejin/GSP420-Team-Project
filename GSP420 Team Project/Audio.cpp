#include "Audio.h"
#include <fmod.hpp>

#pragma comment(lib, "fmod_vc.lib")

Audio::Audio() {
  FMOD::System_Create(&system);
  system->init(MAX_CHANNELS, FMOD_INIT_NORMAL, 0);
  Sound::system = system;
  Song::system = system;
}

Audio::~Audio() {
  system->release();
}

