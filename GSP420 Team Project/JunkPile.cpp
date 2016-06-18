#include "JunkPile.h"

JunkPile::JunkPile(vec2f position) :
  crash("SFX/gun-gunshot-02.mp3"),
  dbgTex(L"Texture/utility box.png"),
  position(position)
{
  //crash.setVolume(1.0f);
  dbgSpr.setBitmap(dbgTex);
  collider.width = 200.0f;
  collider.height = 300.0f;
  snapTo();
}

void JunkPile::update(float dt, float speed) {
  position.x -= speed * dt;
  snapTo();
}

void JunkPile::draw() {
  dbgSpr.draw();
}

void JunkPile::kill() {
  crash.play(); //~~! this is failing. idk why
  alive = false;
  position = vec2f{-1000.0f, -1000.0f};
}

void JunkPile::snapTo() {
  collider.x = position.x - (collider.width / 2);
  collider.y = position.y - collider.height;
  dbgSpr.destRect = collider;
}
