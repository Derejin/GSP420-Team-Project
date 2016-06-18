#include "JunkParticleSystem.h"

JunkParticleSystem::JunkParticleSystem(SharedStore* store, vec2f position) :
  store(store),
  tex(L"Texture/junk.png"),
  crash("SFX/gun-gunshot-02.mp3"),
  basePosition(position)
{
  for(int i = 0; i < PARTICLE_COUNT; i++) { addParticle(); }
}

void JunkParticleSystem::update(float dt, float speed) {
  for(auto& p : particles) { p.position.x -= speed * dt; }
  if(basePosition.x < -2000.0f) { finished = true; }

  if(!active || finished) { return; }
  
  timer -= dt;
  if(timer < 0) { finished = true; }

  for(auto& p : particles) {
    p.rotation += p.rVel * dt;
    p.velocity.y += GRAVITY * dt;
    p.position += p.velocity * dt;
  }
}

void JunkParticleSystem::draw() {
  for(auto& p : particles) {
    p.spr.destRect.x = p.position.x - (p.spr.destRect.width  / 2);
    p.spr.destRect.y = p.position.y - (p.spr.destRect.height / 2);

    store->gfx.setRotation(p.rotation, D2D1::Point2F(p.position.x, p.position.y));
    p.spr.draw();
    store->gfx.resetRotation();
  }
}

void JunkParticleSystem::activate() {
  crash.play();
  for(auto& p : particles) { p.spr.opacity = 0.5f; }
  active = true;
}

void JunkParticleSystem::addParticle() {
  particles.emplace_back();
  auto& p = particles.back();

  const int COLUMNS = 18;
  const int ROWS = 21;

  p.spr.setBitmap(tex);
  p.spr.srcRect.width  /= COLUMNS;
  p.spr.srcRect.height /= ROWS;
  std::uniform_int_distribution<int> swDist(0, COLUMNS - 1);
  std::uniform_int_distribution<int> shDist(0, ROWS - 1);
  p.spr.srcRect.x = p.spr.srcRect.width  * swDist(store->rng);
  p.spr.srcRect.y = p.spr.srcRect.height * shDist(store->rng);
  p.spr.destRect = p.spr.srcRect;
  p.spr.destRect.width  *= PART_SCALE;
  p.spr.destRect.height *= PART_SCALE;

  std::uniform_real_distribution<float> xDist(-100.0f, 100.0f);
  std::uniform_real_distribution<float> yDist(-300.0f, 0.0f);
  p.position = vec2f{xDist(store->rng), yDist(store->rng)};
  p.velocity = p.position * 10.0f;
  p.position += basePosition;

  std::uniform_real_distribution<float> anglePicker(0.0f, 360.0f);
  p.rotation = anglePicker(store->rng);
  p.rVel = p.rotation * 10.0f;
}
