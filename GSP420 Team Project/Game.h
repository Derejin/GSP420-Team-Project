#pragma once
#include "SharedStore.h"
#include "Timer.h"
#include "Scene.h"
#include <memory>
#include "Texture.h"
#include "Plane.h"
#include "Song.h"

//Top-level encapsulation for the game
//Contains the main control loop and the main state machine.
//Create an instance and invoke its .run() member to start the game.

class Game {
public:
  Game();
  void run();

private:
  void fadeOut();
  void fadeIn();

  Timer timer;
  SharedStore store;
  std::unique_ptr<Scene> scene;
  Texture fadeTex;
  Plane fader;

  const float FADE_DURATION = 1.0f;

};
