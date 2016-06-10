#include "TestScene.h"
#include "MessageHandler.h"
#include "InputManager.h"

TestScene::TestScene(InputManager& inputMgr, int screenWidth, int screenHeight) :
  input(&inputMgr),
  font(L"Arial"),
  staticText(L"GSP420 Week 4 Demo\nUse buttons or press 'S' to walk.", &font),
  bgtex(L"tilesetOpenGameBackground_3.png"),
  menu(inputMgr),
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
  btnSpr[0].destRect.x = screenWidth - (btnSpr[0].srcRect.width  + 20);
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

bool TestScene::update() {
  if(input->IsKeyPressed(InputManager::KEY_ESC)) { return false; }

  if(input->MouseMoved())                               { gMessageHandler->HandleMessage(new GSPMessage(RTESTMENU, 0)); }
  if(input->IsMouseTriggered(InputManager::MOUSE_LEFT)) {
    gMessageHandler->HandleMessage(new GSPMessage(RTESTMENU, 1));
    snd.play();
  }
  if(input->IsMouseReleased(InputManager::MOUSE_LEFT))  { gMessageHandler->HandleMessage(new GSPMessage(RTESTMENU, 2)); }
  if(input->IsKeyTriggered(InputManager::KEY_ENTER))    { gMessageHandler->HandleMessage(new GSPMessage(RTESTMENU, 3)); }
  if(input->IsKeyTriggered(InputManager::KEY_UP))       { gMessageHandler->HandleMessage(new GSPMessage(RTESTMENU, 4)); }
  if(input->IsKeyTriggered(InputManager::KEY_DOWN))     { gMessageHandler->HandleMessage(new GSPMessage(RTESTMENU, 5)); }

  if(input->IsKeyPressed(InputManager::KEY_S)) { gMessageHandler->HandleMessage(new GSPMessage(RSTELLA, Stella::WALK)); }

  menu.Update();
  stella.update();
  plane.scrollx += 2;

  return true;
}

void TestScene::draw() {
  batch.draw();
}


