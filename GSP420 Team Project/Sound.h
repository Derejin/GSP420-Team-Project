#pragma once
#include <string>

namespace FMOD {
  class System;
  class Sound;
  class Channel;
}

class Sound {
public:
  void play();
  bool isPlaying() const;
  void setVolume(float volume);

private:
  friend class Audio;
  Sound(const std::string& filename, FMOD::System* system);

  FMOD::Sound* snd;
  FMOD::Channel* chan = nullptr;

};
