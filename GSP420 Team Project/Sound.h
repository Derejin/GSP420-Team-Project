#pragma once
#include <string>

//A Sound object loads a sound into memory and then the play()
//function can be called to play it on demand as many times as
//you like.

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
