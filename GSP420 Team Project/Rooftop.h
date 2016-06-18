#pragma once
#include <vector>
#include "Texture.h"
#include "Sprite.h"
#include "Utility.h"
#include <random>

//#define VIEW_ROOFTOP_COLLIDERS

class Rooftop {
public:
  Rooftop(float prevRoofTailX, float prevRoofHeight, float speedRatio);
  void update(float dt, float speed);
  void draw();
  GSPRect getCollider() const;
  bool out() const;

private:
  void loadTextures();

  const float HEIGHT_LIMIT = 200.0f;
  const float DEPTH_LIMIT = 550.0f;
  const float MAX_STEP_UP = 100.0f;
  const float MAX_STEP_DOWN = 100.0f;
  const float SLOW_GAP_LIMIT = 250.0f;

  static std::mt19937 rng;
  static std::vector<Texture> textures;
  static std::uniform_int_distribution<int> widthDist;
  static std::uniform_int_distribution<size_t> texDist;

  std::vector<Sprite> sprites;
  GSPRect collider;

  #ifdef VIEW_ROOFTOP_COLLIDERS
  Sprite debugSpr;
  Texture debugTex;
  #endif

};
