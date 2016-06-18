#include "GameplayScene.h"
#include "SharedStore.h"
#include <sstream>

GameplayScene::GameplayScene(SharedStore* store) :
  Scene(store),
  font(L"Arial"),
  text(L"derp", &font),
  playerTexture(L"Texture/Player Sprite.png"),
  player(store, playerTexture),
  particles(store, playerTexture),
  junkDist(junkChance)
{
  store->speed = store->START_SPEED;

  rooftops.emplace_back(store, 0.0f, 550.0f, 1.0f);
  for(int i = 0; i < 3; i++) { genNextRoof(); }

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

Scene* GameplayScene::pausedUpdate(float dt) {
  return this;
}

Scene* GameplayScene::playUpdate(float dt) {
  particles.update(dt);
  if(player.isDead()) { return splattedUpdate(dt); }

  updateRooftops(dt);
  updateJunk(dt);

  updatePlayer(dt);
  if(player.isDead()) { return this; }

  store->time += dt;
  if(store->speed < store->MAX_SPEED) { store->speed += 30 * dt; }
  else if(store->speed > store->MAX_SPEED) { store->speed = store->MAX_SPEED; }

  updateScore(dt);
  return this;
}

Scene* GameplayScene::splattedUpdate(float dt) {
  if(store->input.IsKeyTriggered(InputManager::KEY_DASH)) {
    return new GameplayScene(store);
  }

  return this;
}

void GameplayScene::updateJunk(float dt) {
  float rate = store->speed;
  if(player.isDashing()) { rate = store->DASH_SPEED; }

  for(auto& p : piles) { p.update(dt, rate); }

  std::deque<JunkPile> newDeque; //~~@
  for(auto& p : piles) {
    if(p.isAlive()) { newDeque.push_back(p); }
  }

  piles = newDeque;
}

void GameplayScene::updateRooftops(float dt) {
  float rate = store->speed;
  if(player.isDashing()) { rate = store->DASH_SPEED; }

  bg.update(dt, rate); //this doesn't belong here, but whatever

  if(rooftops.front().out()) {
    rooftops.pop_front();
    genNextRoof();
  }

  for(auto& r : rooftops) { r.update(dt, rate); }
}

void GameplayScene::updateScore(float dt) {
  std::wstringstream ss;
  store->score = int(store->time * 1000);
  ss << L"Score: " << store->score;
  text.setString(ss.str());
}

void GameplayScene::updatePlayer(float dt) {
  std::vector<GSPRect> roofColliders;
  for(auto& roof : rooftops) { roofColliders.push_back(roof.getCollider()); }
  player.update(dt, roofColliders, piles);
  if(player.isDashing()) { particles.add(player.getCenterPosition()); }
}

void GameplayScene::draw() {
  bg.draw();
  particles.draw();
  player.draw();
  for(auto& roof : rooftops) { roof.draw(); }
  for(auto& pile : piles) { pile.draw(); }
  text.draw();
}

void GameplayScene::genNextRoof() {
  auto& prev = rooftops.back().getCollider();
  rooftops.emplace_back(store, prev.x + prev.width, prev.y, store->speed / store->START_SPEED);

  if(junkDist(store->rng)) { //add junk
    auto& cur = rooftops.back().getCollider();
    vec2f position{cur.x + (cur.width / 2), cur.y};
    piles.emplace_back(position);
  }

}
