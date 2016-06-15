#pragma once
#include "SharedStore.h"
#include "Timer.h"
#include "Scene.h"
#include <memory>

class Game {
public:
  Game();
  void run();

private:
  Timer timer;
  SharedStore store;
  std::unique_ptr<Scene> scene;

};
