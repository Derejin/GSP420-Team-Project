#include "DashParticleSystem.h"
#include "SharedStore.h"

DashParticleSystem::DashParticleSystem(SharedStore* store, const Texture& texture) :
  tex(texture),
  store(store)
{
}

void DashParticleSystem::add(vec2f position) {
  if(delay > 0) { return; }

  particles.emplace_front(Particle{PARTICLE_MAX_LIFETIME, position});

  auto& spr = particles.front().spr;
  spr.setBitmap(tex);
  spr.srcRect.width /= 8;
  spr.srcRect.x = spr.srcRect.width * 7;

  spr.destRect = spr.srcRect;
  spr.destRect.width  /= 2;
  spr.destRect.height /= 2;

  delay = DELAY_PARTICLE_SECONDS;
}

void DashParticleSystem::update(float dt) {
  delay -= dt;

  for(auto& p : particles) {
    p.lifetime -= dt;
    p.position.x -= store->DASH_SPEED * dt;
  }

  while(!particles.empty() && particles.back().lifetime < 0) {
    particles.pop_back();
  }
}

void DashParticleSystem::draw() {
  for(auto& p : particles) {
    p.spr.opacity = p.lifetime / PARTICLE_MAX_LIFETIME;

    p.spr.destRect = p.spr.srcRect;
    p.spr.destRect.width  *= 0.5f * p.spr.opacity;
    p.spr.destRect.height *= 0.5f * p.spr.opacity;

    p.spr.destRect.moveTo(p.position);
    p.spr.destRect.x -= p.spr.destRect.width  / 2;
    p.spr.destRect.y -= p.spr.destRect.height / 2;

    p.spr.draw();
  }
}
