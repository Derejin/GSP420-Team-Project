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

//This is the gameplay scene, where the player runs across
//the rooftops.

class GameplayScene : public Scene {
public:
  GameplayScene(SharedStore* store);
  ~GameplayScene();
  Scene* update(float dt) override;
  void draw() override;

private:
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
  void genNextRoof();

  void updateHiScores();

  //do not rearrange declaration order past this point

  Texture playerTexture; 

  const float SONG_VOLUME = 0.25f;

  PlayerCharacter player;
  DashParticleSystem particles;

  Sound pauseSnd;
  Sound unpauseSnd;

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

  bool paused = false;

  TitleSceneMessageBox msgReciever;

  bool gotHiScore = false;
  Font hiScoreFont;
  Text hiScoreText;
};
