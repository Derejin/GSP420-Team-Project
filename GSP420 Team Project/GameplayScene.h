#pragma once
#include "Scene.h"
#include "PlayerCharacter.h"
#include <unordered_map>
#include <deque>
#include <random>
#include "Font.h"
#include "Text.h"

class GameplayScene : public Scene {
public:
  GameplayScene(SharedStore* store);
  ~GameplayScene();
  Scene* update(float dt) override;
  void draw() override;

  //MenuManager menu; inherited from Scene

private:
  GSPRect genNextRoof(GSPRect prev);

  Scene* playUpdate(float dt);
  Scene* pausedUpdate(float dt);

  PlayerCharacter player;

  Texture dtex;
  Sprite dspr;

  Font font;
  Text text;

  float time = 0;

  const float START_SPEED = 400.0f;
  const float MAX_SPEED = 1500.0f;
  float speed = START_SPEED;

  std::deque<GSPRect> rooftops;
  std::unordered_map<Pile*, GSPRect> piles;

  //SharedStore* store; inherited from Scene
  bool paused = false;

  std::mt19937 rng;
};
