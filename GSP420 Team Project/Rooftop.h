#pragma once
#include <vector>
#include "Texture.h"
#include "Sprite.h"
#include "Utility.h"
#include <random>

//entity class for rooftops. Primarily concerned with generation,

struct SharedStore;

class Rooftop {
public:
  //use this ctor for the first roof to make sure the player can start fairly
  Rooftop(SharedStore* store, bool first);
  
  //use this for the rest
  //speedRatio is current speed / start speed
  Rooftop(SharedStore* store, float prevRoofTailX, float prevRoofHeight, float speedRatio);

  //scrolls
  void update(float dt, float speed);

  void draw();

  GSPRect getCollider() const;

  //returns true when the roof has scrolled out and can be replaced
  bool out() const;

private:
  void loadTextures();

  const float HEIGHT_LIMIT = 200.0f;
  const float DEPTH_LIMIT = 550.0f;
  const float MAX_STEP_UP = 100.0f;
  const float MAX_STEP_DOWN = 100.0f;
  const float SLOW_GAP_LIMIT = 250.0f;

  static std::vector<Texture> textures;
  static std::uniform_int_distribution<int> widthDist;
  static std::uniform_int_distribution<size_t> texDist;

  std::vector<Sprite> sprites;
  GSPRect collider;

  SharedStore* store;

};
