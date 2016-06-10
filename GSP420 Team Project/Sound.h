#pragma once
#include <string>

namespace FMOD {
  class System;
  class Sound;
  class Channel;
}

class Sound {
public:
  Sound(const std::string& filename);
  ~Sound();

  void play();
  bool isPlaying() const;
  void setVolume(float volume);

private:
  friend class Audio;

  FMOD::Sound* snd = nullptr;
  FMOD::Channel* chan = nullptr;

  static FMOD::System* system;
};
