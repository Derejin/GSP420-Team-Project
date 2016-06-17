#pragma once
#include "Texture.h"
#include "Sprite.h"
#include "Utility.h"
#include <deque>
#include <unordered_map>
#include "InputManager.h"

//#define VIEW_PLAYER_COLLIDERS

class Pile {};

class PlayerCharacter {
public:
  PlayerCharacter();

  void update(float dt, float animFpsScale, InputManager& input, const std::deque<GSPRect>& rooftops, const std::unordered_map<Pile*, GSPRect>& piles);
  void draw();

  bool isDead() const { return splatted; }

private:
  void snapPos();

  #ifdef VIEW_PLAYER_COLLIDERS
  Texture dbgTex;
  Sprite dbgSpr;
  Sprite snsSpr;
  #endif

  Texture tex;
  Sprite spr;
  GSPRect collider;
  GSPRect sensor;
  vec2f position;
  vec2f spriteOffset;
  vec2f colliderOffset;
  vec2f sensorOffset;

  float yVel = 0;
  const float GRAVITY = 2000.0f;
  const float JUMP_SPEED = 1000.0f;
  const float UP_MOMENTUM_LIMIT = 200.0f;
  const float UP_MOMENTUM_CURB = 0.75f;
  const float JUMP_MAX_TIME = 0.125f;
  float jumpTime = 0;

  int frame = 0;
  float frameTimer = 0;

  enum AnimState : int {
    RUNNING,
    JUMPING,
    FALLING,
    SPLATTED
  } animState;

  bool splatted = false;
};
