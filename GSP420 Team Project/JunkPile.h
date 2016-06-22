#pragma once
#include "JunkParticleSystem.h"
#include "Utility.h"
#include <memory>

//Junk pile entity - should be linked with independent
//JunkParticleSystem object, as it does not draw itself

class JunkPile {
public:
  //position is bottom center
  JunkPile(vec2f position, JunkParticleSystem* parts);

  void update(float dt, float speed);

  //trigger destruction of the junk pile (got dashed into)
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
