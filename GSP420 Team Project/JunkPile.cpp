#include "JunkPile.h"

JunkPile::JunkPile(vec2f position, JunkParticleSystem* parts) :
  position(position),
  parts(parts)
{
  collider.width = 200.0f;
  collider.height = 300.0f;
  snapTo();
}

void JunkPile::update(float dt, float speed) {
  position.x -= speed * dt;
  snapTo();
}

void JunkPile::kill() {
  parts->activate();
  alive = false;
  position = vec2f{-1000.0f, -1000.0f};
}

void JunkPile::snapTo() {
  collider.x = position.x - (collider.width / 2);
  collider.y = position.y - collider.height;
}
