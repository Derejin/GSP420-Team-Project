#pragma once
#include "Texture.h"
#include "Sprite.h"

class Stella : public RenderObject {
public:
  Stella();
  void update();
  void draw();

private:
  Texture tex;
  Sprite spr;
  int animstep = 0;

  static const int ROW_NUM = 4;    //row to draw from
  static const int STEP_FREQ = 10; //how many ticks pass before advancing animation frame
  static const int STEP_CELLS = 4; //number of cells in walking loop (horizontal frames)
  static const int WALK_SPEED = 3; //pixels per frame
};
