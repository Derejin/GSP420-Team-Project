#include "Song.h"
#include <fmod.hpp>

FMOD::System* Song::system = nullptr;

Song::Song(const std::string& filename, float vol) {
  system->createStream(filename.c_str(), FMOD_2D|FMOD_LOOP_NORMAL, nullptr, &snd);
  system->playSound(snd, nullptr, true, &chan);
  setVolume(vol);
  chan->setPaused(false);
}

Song::~Song() {
  chan->stop();
  snd->release();
}

void Song::pause(bool pause) {
  chan->setPaused(pause);
}

void Song::setVolume(float volume) {
  chan->setVolume(volume);
}
