#include <fmod.hpp>
#include <string>

#pragma comment(lib, "fmod_vc.lib")

template<class T>
struct FmodPtr {
  T* p = nullptr;

  T* yield() {
    T* temp = p;
    p = nullptr;
    return temp;
  }
  ~FmodPtr() { p->release(); }

  T* operator ->() { return p; }
  T** operator &() { return &p; }
  operator T*() { return p; }
};

class Sound {
public:
  void play() {
    chan->setPaused(false);
  }

  bool isPlaying() const {
    bool rv;
    chan->isPlaying(&rv);
    return rv;
  }

  void setVolume(float volume) {
    chan->setVolume(volume);
  }

private:
  Sound(const std::string& filename, FMOD::System* system) {
    //~~@ look at unused args here
    system->createSound(filename.c_str(), FMOD_2D, nullptr, &snd);
    system->playSound(snd, nullptr, true, &chan);
  }

  friend class Audio;
  FmodPtr<FMOD::Sound> snd;
  FMOD::Channel* chan = nullptr;

};

class Audio {
public:
  Audio() {
    FMOD::System_Create(&system);
    system->init(MAX_CHANNELS, FMOD_INIT_NORMAL, 0);
  }

  Sound createSound(const std::string& filename) {
    return Sound(filename, system);
  }

private:
  static const int MAX_CHANNELS = 512;

  FmodPtr<FMOD::System> system;

};



int main() {
  Audio audio;
  Sound snd = audio.createSound("test.mp3");
  snd.setVolume(0.5f);
  snd.play();
  while(snd.isPlaying());

}

