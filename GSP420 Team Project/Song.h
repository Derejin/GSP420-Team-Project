#pragma once
#include <string>

namespace FMOD {
  class System;
  class Sound;
  class Channel;
}

class Song {
public:
  Song(const std::string& filename, float vol = 1.0f);
  ~Song();

  void pause(bool pause);
  void setVolume(float volume);

private:
  friend class Audio;

  FMOD::Sound* snd = nullptr;
  FMOD::Channel* chan = nullptr;

  static FMOD::System* system;
};
