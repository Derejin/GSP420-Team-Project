#include "Song.h"
#include <fmod.hpp>

FMOD::System* Song::system = nullptr;

Song::Song(const std::string& filename) {
  //~~@ look at unused args here
  system->createStream(filename.c_str(), FMOD_LOOP_NORMAL, nullptr, &snd);
  system->playSound(snd, nullptr, false, &chan);
}

Song::~Song() {
  snd->release();
}

void Song::pause(bool pause) {
  chan->setPaused(pause);
}

void Song::setVolume(float volume) {
  chan->setVolume(volume);
}
