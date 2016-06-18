#include "Sound.h"
#include <fmod.hpp>
#include <cassert>

FMOD::System* Sound::system = nullptr;

Sound::Sound(const std::string& filename) {
  auto result = system->createSound(filename.c_str(), FMOD_2D, nullptr, &snd);
  result = system->playSound(snd, nullptr, true, &chan);
}

Sound::~Sound() {
  snd->release();
}

void Sound::play() {
  auto result = chan->setPosition(0, FMOD_TIMEUNIT_MS);
  result = chan->setPaused(false);
}

bool Sound::isPlaying() const {
  bool rv;
  chan->isPlaying(&rv);
  return rv;
}

void Sound::setVolume(float volume) {
  chan->setVolume(volume);
}
