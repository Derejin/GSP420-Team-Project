#pragma once
#include "JunkParticleSystem.h"
#include "Utility.h"
#include <memory>

class JunkPile {
public:
  JunkPile(vec2f position, JunkParticleSystem* parts);
  void update(float dt, float speed);

  void kill();

  bool isAlive() const { return alive; }
  GSPRect getCollider() const { return collider; }

private:
  void snapTo();

  vec2f position;
  GSPRect collider;

  bool alive = true;

  JunkParticleSystem* parts;

};
