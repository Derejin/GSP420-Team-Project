#include "Stella_temp.h"


const int Stella::facingMap[Stella::NUM_DIRECTIONS] = { 0, 4, 2, 7, 3, 6, 1, 5 };

Stella::Stella() : tex(L"stella_walk_2.png") {
  spr.setBitmap(tex);

  spr.srcRect.width /= 4;
  spr.srcRect.height /= 8;
  spr.srcRect.y = spr.srcRect.height * facingMap[facing];

  spr.destRect = spr.srcRect;
  spr.destRect.x = 10;
  spr.destRect.y = 300;
}

void Stella::update() {
  processQueue();

  animstep++;
  int frameNum = (animstep / STEP_FREQ) % STEP_CELLS;
  spr.srcRect.x = spr.srcRect.width * frameNum;
}

void Stella::draw() {
  spr.draw();
}

void Stella::DecodeMessage(int messageValue) {

  switch(messageValue) {
  case TURN_LEFT:
    facing++;
    if(facing >= NUM_DIRECTIONS) { facing -= NUM_DIRECTIONS; }
    spr.srcRect.y = spr.srcRect.height * facingMap[facing];
    break;
  case TURN_RIGHT:
    facing--;
    if(facing < 0) { facing += NUM_DIRECTIONS; }
    spr.srcRect.y = spr.srcRect.height * facingMap[facing];
    break;
  case WALK:
    walk();
    break;
  }

}

void Stella::walk() {
  switch(facing) {
  case 0: //s
    spr.destRect.y += walkLength;
    break;
  case 1: //se
    spr.destRect.y += walkLength;
    spr.destRect.x += walkLength;
    break;
  case 2: //e
    spr.destRect.x += walkLength;
    break;
  case 3: //ne
    spr.destRect.y -= walkLength;
    spr.destRect.x += walkLength;
    break;
  case 4: //n
    spr.destRect.y -= walkLength;
    break;
  case 5: //nw
    spr.destRect.y -= walkLength;
    spr.destRect.x -= walkLength;
    break;
  case 6: //w
    spr.destRect.x -= walkLength;
    break;
  case 7: //sw
    spr.destRect.y += walkLength;
    spr.destRect.x -= walkLength;
    break;
  }
}

