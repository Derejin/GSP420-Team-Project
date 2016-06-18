#pragma once

#include "Texture.h"
#include "Sprite.h"
#include "Sound.h"
#include "Utility.h"

class JunkPile {
public:
  JunkPile(vec2f position);
  void update(float dt, float speed);
  void draw();

  void kill();

  bool isAlive() const { return alive; }
  GSPRect getCollider() const { return collider; }

private:
  void snapTo();

  vec2f position;
  GSPRect collider;

  Sound crash;

  bool alive = true;

  Texture dbgTex;
  Sprite dbgSpr;

};
