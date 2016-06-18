#pragma once
#include "Scene.h"
#include "PlayerCharacter.h"
#include <unordered_map>
#include <deque>
#include "SharedStore.h"
#include "Font.h"
#include "Text.h"
#include "Rooftop.h"
#include "DashParticleSystem.h"
#include "MultiBackground.h"
#include "JunkPile.h"
#include "Song.h"
#include <memory>

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
  void updateJunk(float dt);
  void updateScore(float dt);
  void updatePlayer(float dt);

  Texture playerTexture; //do not rearrange declaration order

  Song song;

  PlayerCharacter player;
  DashParticleSystem particles;

  MultiBackground bg;

  Font font;
  Text text;

  std::deque<Rooftop> rooftops;
  std::deque<JunkPile> piles;
  std::vector<std::unique_ptr<JunkParticleSystem>> junkParticles;

  const float junkChance = 0.33f;
  std::bernoulli_distribution junkDist;

  //SharedStore* store; inherited from Scene
  bool paused = false;

};
