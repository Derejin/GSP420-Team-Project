#include "GameplayScene.h"
#include "SharedStore.h"
#include <sstream>

GameplayScene::GameplayScene(SharedStore* store) :
  Scene(store),
  dtex(L"Texture/utility box.png"),
  font(L"Arial"),
  text(L"derp", &font),
  rng(std::random_device{}())
{

  rooftops.emplace_back(0.0f,500.0f,1500.0f,1000.0f);
  for(int i = 0; i < 10; i++) {
    rooftops.push_back(genNextRoof(rooftops.back()));
  }

  dspr.setBitmap(dtex);

  text.setRect(GSPRect(10, 10, 300, 300));
  font.setColor(D2D1::ColorF::White);

}

GameplayScene::~GameplayScene() {
}

Scene* GameplayScene::update(float dt) {
  if(store->input.IsKeyPressed(InputManager::KEY_ESC)) { return nullptr; }

  if(paused) { return pausedUpdate(dt); }
  return playUpdate(dt);
}

Scene* GameplayScene::playUpdate(float dt) {
  if(player.isDead()) {
    if(store->input.IsKeyTriggered(InputManager::KEY_DASH)) {
      return new GameplayScene(store);
    }

    return this;
  }


  if(rooftops.front().x < -rooftops.front().width) {
    rooftops.pop_front();
    rooftops.push_back(genNextRoof(rooftops.back()));
  }

  player.update(dt, speed / START_SPEED, store->input, rooftops, piles);
  if(player.isDead()) { return this; }

  if(speed < MAX_SPEED) { speed += 30 * dt; }
  else if(speed > MAX_SPEED) { speed = MAX_SPEED; }

  for(auto& r : rooftops) {
    r.moveBy(vec2f{-speed * dt, 0});;
  }

  time += dt;
  std::wstringstream ss;
  ss << time;
  text.setString(ss.str());
  return this;
}

Scene* GameplayScene::pausedUpdate(float dt) {
  return this;
}


void GameplayScene::draw() {
  player.draw();
  for(auto r : rooftops) {
    dspr.destRect = r;
    dspr.draw();
  }

  text.draw();
}

GSPRect GameplayScene::genNextRoof(GSPRect prev) {
  const float HEIGHT_LIMIT = 200.0f;
  const float DEPTH_LIMIT = 550.0f;

  float high = prev.y - 100;
  if(high < HEIGHT_LIMIT) { high = HEIGHT_LIMIT; }
  float low = prev.y + 100;
  if(low > DEPTH_LIMIT) { low = DEPTH_LIMIT; }

  std::uniform_real_distribution<float> heightRand(high, low);

  float gap_limit = 250.0f * (speed / START_SPEED);
  std::uniform_real_distribution<float> gapRand(10.0f, gap_limit);

  std::uniform_real_distribution<float> wideRand(speed * 0.75f, speed * 1.5f);

  prev.x += prev.width + gapRand(rng);
  prev.y = heightRand(rng);
  prev.width = wideRand(rng);

  return prev;
}
