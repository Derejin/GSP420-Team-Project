#include "Rooftop.h"
#include "SharedStore.h"

std::vector<Texture> Rooftop::textures;
std::uniform_int_distribution<int> Rooftop::widthDist(5,15);
std::uniform_int_distribution<size_t> Rooftop::texDist;

Rooftop::Rooftop(SharedStore* store, float prevRoofTailX, float prevRoofHeight, float speedRatio) {
  if(textures.empty()) { loadTextures(); }

  float high = prevRoofHeight - MAX_STEP_UP;
  if(high < HEIGHT_LIMIT) { high = HEIGHT_LIMIT; }

  float low = prevRoofHeight + MAX_STEP_DOWN;
  if(low > DEPTH_LIMIT) { low = DEPTH_LIMIT; }

  std::uniform_real_distribution<float> heightRand(high, low);

  float gap_limit = SLOW_GAP_LIMIT * speedRatio;
  std::uniform_real_distribution<float> gapRand(0.0f, gap_limit);

  int width = widthDist(store->rng);

  collider.x = prevRoofTailX + gapRand(store->rng);
  collider.y = heightRand(store->rng);
  collider.width = width * 100.0f;
  collider.height = 1000.0f;

  size_t which = texDist(store->rng);
  for(int i = 0; i < width; i++) {
    sprites.emplace_back();
    auto& spr = sprites.back();
    spr.setBitmap(textures[which]);
    spr.destRect = spr.srcRect;
    spr.destRect.y = collider.y;
  }

  #ifdef VIEW_ROOFTOP_COLLIDERS
  debugSpr.setBitmap(debugTex);
  #endif
}

void Rooftop::update(float dt, float speed) {
  collider.x -= speed * dt;
  float x = collider.x;
  for(auto& spr : sprites) {
    spr.destRect.x = x;
    x += spr.destRect.width;
  }
}

void Rooftop::draw() {
  for(auto& spr : sprites) { spr.draw(); }

  #ifdef VIEW_ROOFTOP_COLLIDERS
  debugSpr.destRect = collider;
  debugSpr.draw();
  #endif
}

GSPRect Rooftop::getCollider() const {
  return collider;
}

bool Rooftop::out() const {
  return collider.x < -collider.width;
}

void Rooftop::loadTextures() {
  textures.emplace_back(L"Texture/Rooftops/Brick.png");
  textures.emplace_back(L"Texture/Rooftops/Skyscraper.png");

  texDist = std::uniform_int_distribution<size_t>(0, textures.size() - 1);
}
