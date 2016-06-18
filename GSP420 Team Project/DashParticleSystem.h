#pragma once
#include "Utility.h"
#include "Texture.h"
#include "Sprite.h"
#include <deque>

struct SharedStore;

class DashParticleSystem {
public:
  DashParticleSystem(SharedStore* store, const Texture& texture);
  void add(vec2f position);
  void update(float dt);
  void draw();

private:
  SharedStore* store;

  struct Particle {
    float lifetime;
    vec2f position;
    Sprite spr;
  };

  std::deque<Particle> particles;

  Texture tex;

  const float PARTICLE_MAX_LIFETIME = 0.125f;
  const float DELAY_PARTICLE_SECONDS = 0.0625f;
  float delay = 0;

};
