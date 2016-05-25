#include "Stella_temp.h"

Stella::Stella() : tex(L"stella_walk_2.png") {
  spr.setBitmap(tex);

  spr.srcRect.width /= 4;
  spr.srcRect.height /= 8;
  spr.srcRect.y = spr.srcRect.height * ROW_NUM;

  spr.destRect = spr.srcRect;
  spr.destRect.x = 10;
  spr.destRect.y = 300;
}

void Stella::update() {
  animstep++;
  int frameNum = (animstep / STEP_FREQ) % STEP_CELLS;

  spr.srcRect.x = spr.srcRect.width * frameNum;
  spr.destRect.x += WALK_SPEED;
}

void Stella::draw() {
  spr.draw();
}

