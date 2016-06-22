#pragma once
#include "Texture.h"
#include "Plane.h"
#include "DepthBatch.h"

//scrolling parallax background for gameplay scene

class MultiBackground {
public:
  MultiBackground();
  void update(float dt, float speed);
  void draw();

private:
  Texture skyTex;
  Texture cityTex;
  Texture waterTex;
  Texture rocksTex;

  Plane sky;
  Plane city;
  Plane water;
  Plane rocks;

  DepthBatch batch;

  const float skyRate   = 0.1f;
  const float cityRate  = 0.4f;
  const float waterRate = 0.6f;
  const float rocksRate = 0.9f;

};
