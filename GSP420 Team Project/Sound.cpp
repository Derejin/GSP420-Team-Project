#include "Sound.h"
#include <fmod.hpp>

FMOD::System* Sound::system = nullptr;

Sound::Sound(const std::string& filename) {
  //~~@ look at unused args here
  system->createSound(filename.c_str(), FMOD_2D, nullptr, &snd);
  system->playSound(snd, nullptr, true, &chan);
}

Sound::~Sound() {
  snd->release();
}

void Sound::play() {
  chan->setPosition(0, FMOD_TIMEUNIT_MS);
  chan->setPaused(false);
}

bool Sound::isPlaying() const {
  bool rv;
  chan->isPlaying(&rv);
  return rv;
}

void Sound::setVolume(float volume) {
  chan->setVolume(volume);
}
