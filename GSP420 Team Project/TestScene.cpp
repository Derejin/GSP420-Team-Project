#include "TestScene.h"
#include "MessageHandler.h"
#include "InputManager.h"
#include "SharedStore.h"

TestScene::TestScene(SharedStore* store) :
  Scene(store),
  font(L"Arial"),
  staticText(L"GSP420 Week 4 Demo\nUse buttons or press 'S' to walk.", &font),
  bgtex(L"tilesetOpenGameBackground_3.png"),
  snd("SFX/button-37.mp3"),
  song("BGM/Undaunted.mp3")
{
  gMessageHandler->AddRecipient(&menu, RTESTMENU);

  font.setColor(D2D1::ColorF(0,1));
  font.setSize(40.0f);

  staticText.setRect(GSPRect(200.f, 50.f, 600.f, 200.f));
  batch.addRO(&staticText);
  staticText.z = 0;

  batch.addRO(&stella);
  stella.z = 100;
  gMessageHandler->AddRecipient(&stella, RSTELLA);

  plane.setTexture(bgtex);
  batch.addRO(&plane);
  plane.z = -100;

  Texture buttons(L"buttons.png");
  //temporary sprites for copying into menu
  std::vector<Sprite> btnSpr;

  //configure the first one - button texture is three buttons tiled directly on top of eachother
  btnSpr.emplace_back();
  btnSpr[0].setBitmap(buttons);
  btnSpr[0].srcRect.height /= 3;

  btnSpr[0].destRect = btnSpr[0].srcRect;
  btnSpr[0].destRect.x = store->screenWidth - (btnSpr[0].srcRect.width  + 20);
  btnSpr[0].destRect.y = 20;

  //make copies and adjust them
  btnSpr.push_back(btnSpr[0]);
  btnSpr.back().srcRect.y += btnSpr.back().srcRect.height;
  btnSpr.push_back(btnSpr.back());
  btnSpr.back().srcRect.y += btnSpr.back().srcRect.height;

  menu.AddButton(btnSpr[0], btnSpr[1], btnSpr[2], btnSpr[0].destRect, GSPMessage(RSTELLA, Stella::TURN_LEFT));
  //have to move the destRect of all three sprites, then add next button
  for(auto& spr : btnSpr) { spr.destRect.y += spr.destRect.height + 20; }
  menu.AddButton(btnSpr[0], btnSpr[1], btnSpr[2], btnSpr[0].destRect, GSPMessage(RSTELLA, Stella::WALK));
  for(auto& spr : btnSpr) { spr.destRect.y += spr.destRect.height + 20; }
  menu.AddButton(btnSpr[0], btnSpr[1], btnSpr[2], btnSpr[0].destRect, GSPMessage(RSTELLA, Stella::TURN_RIGHT));
  batch.addRO(&menu);

  menuLabels.emplace_back(L"Turn Left", &font);
  menuLabels.emplace_back(L"Step", &font);
  menuLabels.emplace_back(L"Turn Right", &font);

  auto rect = btnSpr[0].destRect;
  rect.x += 10;
  rect.y = 50 - 120;
  for(size_t i = 0; i < menuLabels.size(); i++) {
    rect.y += 120;
    menuLabels[i].setRect(rect);
    batch.addRO(&menuLabels[i]);
  }
}

TestScene::~TestScene() {
  //gMessageHandler->RemoveRecipient(RTESTMENU);
}

Scene* TestScene::update(float dt) {
  menu.Update();

  if(store->input.IsKeyPressed(InputManager::KEY_ESC)) { return nullptr; }
  if(store->input.IsKeyPressed(InputManager::KEY_S)) { gMessageHandler->HandleMessage(new GSPMessage(RSTELLA, Stella::WALK)); }

  stella.update();
  plane.scrollx += 2;

  return this;
}

void TestScene::draw() {
  batch.draw();
}


