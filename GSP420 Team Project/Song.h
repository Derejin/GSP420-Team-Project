#pragma once
#include <string>

//Creating a song object will stream the indicated sound file from disk
//and play it back in an infinite loop. The playback will begin automatically.

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
