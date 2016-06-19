#pragma once
#include "Texture.h"
#include "Sprite.h"
#include "Utility.h"
#include <deque>
#include <unordered_map>
#include "InputManager.h"
#include "Sound.h"
#include "JunkPile.h"

struct SharedStore;

class PlayerCharacter {
public:
  PlayerCharacter(SharedStore* store, const Texture& texture);

  void update(float dt, const std::vector<GSPRect>& rooftops, std::deque<JunkPile>& piles);
  void draw();

  bool isDead() const { return splatted; }
  bool isDashing() const { return dashing; }
  vec2f getCenterPosition() const;

private:
  void snapPos();

  void checkRooftops(const std::vector<GSPRect>& rooftops);
  void checkPiles(std::deque<JunkPile>& piles);
  void updateJumpLand(float dt);
  void updateDash(float dt);
  void doSplat();

  SharedStore* store;

  Sound leftStepSound;
  Sound rightStepSound;
  Sound dashSound;
  Sound splatSound;
  Sound jumpSound;

  Texture tex;
  Texture dizzyTex;
  Sprite spr;
  GSPRect collider;
  GSPRect sensor;
  vec2f position;
  vec2f spriteOffset;
  vec2f colliderOffset;
  vec2f sensorOffset;

  const int SPRITE_FRAMES = 8;
  const int RUN_FRAMES = 5;
  const int DIZZY_FRAMES = 2;
  const float SPRITE_SCALE = 0.5f;

  float yVel = 0;
  const float GRAVITY = 2000.0f;
  const float JUMP_SPEED = 1000.0f;
  const float UP_MOMENTUM_LIMIT = 200.0f;
  const float UP_MOMENTUM_CURB = 0.75f;
  const float JUMP_MAX_TIME = 0.125f;
  float jumpTime = 0;

  int frame = 0;
  float frameTimer = 0;

  enum AnimState {
    RUNNING,
    JUMPING,
    FALLING,
    DASHING,
    SPLATTED
  };

  bool splatted = false;

  bool canDash = false;
  bool dashing = false;

  const float DASH_DELAY = 0.5f;
  const float DASH_SIZE = 0.25f;
  float dashTimer = 0;

  bool grounded;

};
