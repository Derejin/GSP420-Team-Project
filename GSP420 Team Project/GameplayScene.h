#pragma once
#include "Scene.h"
#include "PlayerCharacter.h"
#include <unordered_map>
#include <deque>
#include <random>
#include "Font.h"
#include "Text.h"
#include "Rooftop.h"
#include "DashParticleSystem.h"
#include "MultiBackground.h"

class GameplayScene : public Scene {
public:
  GameplayScene(SharedStore* store);
  ~GameplayScene();
  Scene* update(float dt) override;
  void draw() override;

  //MenuManager menu; inherited from Scene

private:
  void genNextRoof();

  Scene* pausedUpdate(float dt);
  Scene* playUpdate(float dt);
  Scene* splattedUpdate(float dt);
  void updateRooftops(float dt);
  void updateScore(float dt);
  void updatePlayer(float dt);

  Texture playerTexture; //do not rearrange declaration order

  PlayerCharacter player;
  DashParticleSystem particles;
  MultiBackground bg;

  Font font;
  Text text;

  std::deque<Rooftop> rooftops;
  std::unordered_map<Pile*, GSPRect> piles;

  //SharedStore* store; inherited from Scene
  bool paused = false;

};
