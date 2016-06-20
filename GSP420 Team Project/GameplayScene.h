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
#include "Texture.h"
#include "TitleSceneMessageBox.h"
#include "MessageHandler.h"

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
  void updateJunkParticles(float dt);
  void updateScore(float dt);
  void updatePlayer(float dt);
  void setPaused(bool pause);
  void createPauseMenu();

  Texture playerTexture; //do not rearrange declaration order

  const float SONG_VOLUME = 0.25f;
  //Song song;

  PlayerCharacter player;
  DashParticleSystem particles;

  MultiBackground bg;
  Texture blackTex;
  Plane pausePlane;

  Font font;
  Text scoreText;
  Sprite scoreBG;

  Font pauseFont;
  std::vector<Text> menuText;

  bool justDidJunk = true;
  std::deque<Rooftop> rooftops;
  std::deque<JunkPile> piles;
  std::vector<std::unique_ptr<JunkParticleSystem>> junkParticles;
  Texture junkTexture;

  const float junkChance = 0.33f;
  std::bernoulli_distribution junkDist;

  //SharedStore* store; inherited from Scene
  bool paused = false;

  TitleSceneMessageBox msgReciever;

};
