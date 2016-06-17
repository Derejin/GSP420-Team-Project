#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter() :
  tex(L"Texture/Player Sprite.png")
  #ifdef VIEW_PLAYER_COLLIDERS
  , dbgTex(L"Texture/utility box.png")
  #endif
{
  //~~@ magic numbers
  spr.setBitmap(tex);
  spr.srcRect.width /= 8;

  spr.destRect = spr.srcRect;
  spr.destRect.width /= 2;
  spr.destRect.height /= 2;

  collider = spr.destRect;
  collider.width /= 2;
  collider.height /= 3;

  sensor = collider;
  sensor.height = 2;
  
  spriteOffset = vec2f{-(spr.destRect.width / 2), 10 - spr.destRect.height};
  colliderOffset = vec2f{-(collider.width / 2), -spr.destRect.height / 2};
  sensorOffset = vec2f{-(sensor.width / 2), 0};
  position = vec2f{300, 300};

  #ifdef VIEW_PLAYER_COLLIDERS
  dbgSpr.setBitmap(dbgTex);
  snsSpr.setBitmap(dbgTex);
  #endif
}

void PlayerCharacter::update(float dt, float animFpsScale, InputManager& input, const std::deque<GSPRect>& rooftops, const std::unordered_map<Pile*, GSPRect>& piles) {
  position.y += yVel * dt;

  std::vector<GSPRect> roofHits = collider.testOverlap(rooftops);
  if(roofHits.size()) {
    splatted = true;
    return;
  }

  roofHits = sensor.testOverlap(rooftops);
  bool grounded = !roofHits.empty();
  bool jumpButton = input.IsKeyPressed(InputManager::KEY_JUMP); //~~_
  if(grounded) {
    animState = RUNNING;

    yVel = 0;

    float rooftop = 900.0f; //~~@
    for(auto r : roofHits) {
      if(r.y < rooftop) { rooftop = r.y; }
    }

    position.y = rooftop;

    if(jumpButton) { 
      position.y -= 3;
    }
    else {
      jumpTime = JUMP_MAX_TIME;
    }
  }
  else { //not grounded
    if(jumpTime > 0 && jumpButton) {
      yVel = -JUMP_SPEED;
      jumpTime -= dt;
    }
    else {
      jumpTime = 0;
      if(yVel < -UP_MOMENTUM_LIMIT) { yVel *= UP_MOMENTUM_CURB; }
      yVel += GRAVITY * dt;
    }

    animState = JUMPING;
    if(yVel > 50) { animState = FALLING; }

  }

  float fps = 5 * animFpsScale;
  float hz = 1.0f / fps;
  while(frameTimer > hz) {
    frame = (frame + 1) % 5; //~~@ magic
    frameTimer -= hz;
  }
  frameTimer += dt;

  snapPos();
}

void PlayerCharacter::draw() {
  switch(animState) {
  case RUNNING:
    spr.srcRect.x = frame * spr.srcRect.width;
    break;
  case JUMPING:
    spr.srcRect.x = 5 * spr.srcRect.width;
    break;
  case FALLING:
    spr.srcRect.x = 6 * spr.srcRect.width;
    break;
  case SPLATTED:
    break;
  }
  spr.draw();

  #ifdef VIEW_PLAYER_COLLIDERS
  dbgSpr.draw();
  snsSpr.draw();
  #endif
}

void PlayerCharacter::snapPos() {
  spr.destRect.moveTo(position + spriteOffset);
  collider.moveTo(position + colliderOffset);
  sensor.moveTo(position + sensorOffset);

  #ifdef VIEW_PLAYER_COLLIDERS
  dbgSpr.destRect = collider;
  snsSpr.destRect = sensor;
  #endif
}


