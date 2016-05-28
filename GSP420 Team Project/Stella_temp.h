#pragma once
#include "Texture.h"
#include "Sprite.h"
#include "BaseRecipient.h"

class Stella : public BaseRecipient, public RenderObject {
public:
  Stella();
  void update();
  void draw();
  void DecodeMessage(int messageValue);

  enum Command : int {
    TURN_LEFT,
    WALK,
    TURN_RIGHT
  };

private:
  void walk();

  Texture tex;
  Sprite spr;
  int animstep = 0;
  int facing = 0;
  const float walkLength = 5.0f;

  //the spritesheet is in weird row order, so this maps it
  //zero is down, map proceeds counter-clockwise
  static const int NUM_DIRECTIONS = 8;
  static const int facingMap[NUM_DIRECTIONS];

  static const int STEP_FREQ = 10; //how many ticks pass before advancing animation frame
  static const int STEP_CELLS = 4; //number of cells in walking loop (horizontal frames)
  static const int WALK_SPEED = 3; //pixels per frame
};
