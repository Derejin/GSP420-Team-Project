#pragma once
#include <vector>
#include "Texture.h"
#include "Sprite.h"
#include "Sound.h"
#include "SharedStore.h"

//Particle system for junk piles.

class JunkParticleSystem {
public:
  //position is the bottom center

  JunkParticleSystem(SharedStore* store, vec2f position, Texture* tex);
  void update(float dt, float speed);
  void draw();

  bool isFinished() const { return finished; }

  //begins 'explosion' effect
  void activate();

private:
  SharedStore* store;

  Sound crash;
  Texture* tex;
  bool finished = false;
  bool active = false;
  float timer = 3.0f;

  const float GRAVITY = 2000.0f;
  const float PART_SCALE = 3.0f;
  const int PARTICLE_COUNT = 60;

  vec2f basePosition;

  struct Particle {
    Sprite spr;
    vec2f position;
    vec2f velocity;
    float rotation;
    float rVel;
  };

  void addParticle();

  std::vector<Particle> particles;

};
