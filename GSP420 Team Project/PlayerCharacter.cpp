#include "PlayerCharacter.h"
#include "SharedStore.h"

PlayerCharacter::PlayerCharacter(SharedStore* store, const Texture& texture) :
  store(store),
  tex(texture)
{
  spr.setBitmap(tex);
  spr.srcRect.width /= SPRITE_FRAMES;

  spr.destRect = spr.srcRect;
  spr.destRect.width  *= SPRITE_SCALE;
  spr.destRect.height *= SPRITE_SCALE;

  collider = spr.destRect;
  collider.width  /= 2;
  collider.height /= 3;

  sensor = collider;
  sensor.height = 2;
  
  //magic numbers, but this is pretty fiddly, so they stay for now
  spriteOffset = vec2f{-(spr.destRect.width / 2), 10 - spr.destRect.height};
  colliderOffset = vec2f{-(collider.width / 2), -spr.destRect.height / 2};
  sensorOffset = vec2f{-(sensor.width / 2), 0};
  position = vec2f{300, 300};

}

void PlayerCharacter::update(float dt, const std::vector<GSPRect>& rooftops, const std::unordered_map<Pile*, GSPRect>& piles) {
  checkRooftops(rooftops);
  checkPiles(piles);
  if(splatted) { return; }

  updateVertical(dt);
  updateDash(dt);

  position.y += yVel * dt;
  snapPos();

  frameTimer += dt;
}

void PlayerCharacter::checkRooftops(const std::vector<GSPRect>& rooftops) {
  for(auto r : rooftops) {
    if(r.testOverlap(collider)) {
      splatted = true;
      break;
    }
  }

  auto roofSteps = sensor.testOverlap(rooftops);
  grounded = !roofSteps.empty();

  //player is standing on rooftop, so set elevation accordingly
  for(auto r : roofSteps) {
    if(r.y < position.y) { position.y = r.y; }
  }

}

void PlayerCharacter::checkPiles(const std::unordered_map<Pile*, GSPRect>& piles) {
  //~~_
}

void PlayerCharacter::updateVertical(float dt) {
  bool jumpButton = store->input.IsKeyPressed(InputManager::KEY_JUMP);

  if(grounded) {
    yVel = 0;

    if(jumpButton) { position.y -= 3; } //get clearance for sensor
    else { jumpTime = JUMP_MAX_TIME; } //on ground and button released, so refill jump time

  }
  else { //not grounded
    yVel += GRAVITY * dt;

    if(jumpButton && jumpTime > 0) { //jump in progress
      yVel = -JUMP_SPEED;
      jumpTime -= dt;
    }
    else {
      jumpTime = 0; //jump is over, so empty jump time
      if(yVel < -UP_MOMENTUM_LIMIT) { yVel *= UP_MOMENTUM_CURB; } //curb excessive climb rates
    }

  }

}

void PlayerCharacter::updateDash(float dt) {
  bool button = store->input.IsKeyPressed(InputManager::KEY_DASH);

  dashTimer -= dt;
  if(grounded && dashTimer < -DASH_DELAY) { canDash = true; }

  if(button) {
    if(dashing) {
      yVel = 0;
      dashing = dashTimer > 0;
    }
    else if(canDash) {
      dashTimer = DASH_SIZE;
      dashing = true;
      canDash = false;
    }

  }
  else { //not button
    if(dashing) { dashTimer = 0; }
    dashing = false;
  }

}


void PlayerCharacter::draw() {
  AnimState animState = JUMPING;
  if(grounded)  { animState = RUNNING; }
  if(yVel > 50) { animState = FALLING; }
  if(dashing)   { animState = DASHING; }
  if(splatted)  { animState = SPLATTED; }

  switch(animState) {
  case RUNNING:
    {
      float animFpsScale = store->speed / store->START_SPEED;
      float fps = 5 * animFpsScale;
      float hz = 1.0f / fps;
      while(frameTimer > hz) {
        frame = (frame + 1) % RUN_FRAMES;
        frameTimer -= hz;
      }
      spr.srcRect.x = frame * spr.srcRect.width;
    }
    break;
  case JUMPING:
    spr.srcRect.x = 5 * spr.srcRect.width;
    break;
  case FALLING:
    spr.srcRect.x = 6 * spr.srcRect.width;
    break;
  case DASHING:
    spr.srcRect.x = 7 * spr.srcRect.width;
    break;
  case SPLATTED:
    break;
  }

  spr.draw();

}

vec2f PlayerCharacter::getCenterPosition() const {
  vec2f center{spr.destRect.x, spr.destRect.y};
  center.x += spr.destRect.width  / 2;
  center.y += spr.destRect.height / 2;
  return center;
}

void PlayerCharacter::snapPos() {
  spr.destRect.moveTo(position + spriteOffset);
  collider.moveTo(position + colliderOffset);
  sensor.moveTo(position + sensorOffset);

}
