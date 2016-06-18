#include "MultiBackground.h"

MultiBackground::MultiBackground() :
  skyTex(L"Texture/Planes/sky.png"),
  cityTex(L"Texture/Planes/city.png"),
  waterTex(L"Texture/Planes/water.png"),
  rocksTex(L"Texture/Planes/rocks.png")
{
  sky.setTexture(skyTex);
  batch.addRO(&sky);
  city.setTexture(cityTex);
  batch.addRO(&city);
  water.setTexture(waterTex);
  batch.addRO(&water);
  rocks.setTexture(rocksTex);
  batch.addRO(&rocks);
}

void MultiBackground::update(float dt, float speed) {
  float motion = speed * dt;
  sky.scrollx   += motion * skyRate;
  city.scrollx  += motion * cityRate;
  water.scrollx += motion * waterRate;
  rocks.scrollx += motion * rocksRate;
}

void MultiBackground::draw() {
  batch.draw();
}
