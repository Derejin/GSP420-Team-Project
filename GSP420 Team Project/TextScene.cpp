#include "TextScene.h"
#include "MessageHandler.h"
#include "SharedStore.h"
#include <fstream>
#include <sstream>
#include <string>
#include "TitleScene.h"

TextScene::TextScene(SharedStore* store) :
  bgTex(L"Texture/ColtonTitleBackground.png"),
  black(L"Texture/Planes/black.png"),
  font(L"Arial"),
  menufont(L"Arial"),
  text(L"", &font),
  menuText(L"Back", &menufont),
  Scene(store)
{
  //adding song information to the store for smooth music transition
  store->oldBaseVol = store->songBaseVol;
  store->songBaseVol = SONG_VOLUME;
  store->songPath = "BGM/Monkeys Spinning Monkeys.mp3";

  //registering the button and the button responder
  gMessageHandler->AddRecipient(&menu, RTEXTMENU);
  store->msgTgt = RTEXTMENU;
  gMessageHandler->AddRecipient(&messageBox, RTEXTSCENE);

  //bg
  bg.setTexture(bgTex);

  //load text
  std::wstringstream ss;
  {
    std::wifstream file(store->textFile);
    assert(file && "Failed to open file.");
    ss << file.rdbuf();
  }

  //primary text
  GSPRect textRect(0, 5.0f, 500.0f, store->screenHeight - 10.0f);
  textRect.x = (store->screenWidth - textRect.width) / 2;
  textBox.setBitmap(black);
  textBox.destRect = textRect;
  textBox.opacity = 0.8f;
  font.setSize(10.0f);
  textRect.moveBy(vec2f{10.0f, 5.0f});
  text.setRect(textRect);
  text.setString(ss.str());

  //button
  menufont.setSize(35.0f);
  menufont.setColor(D2D1::ColorF::Black);
  Texture btnTex(L"Texture/buttons.png");
  std::vector<Sprite> btnSpr;

  //config first button; button textures are three buttons tiled one above another
  btnSpr.emplace_back();
  btnSpr[0].setBitmap(btnTex);
  btnSpr[0].srcRect.height /= 3;

  btnSpr[0].destRect = GSPRect(0, 0, 100.0f, 50.0f);
  btnSpr[0].destRect.x = store->screenWidth - (btnSpr[0].destRect.width + 10);
  btnSpr[0].destRect.y = store->screenHeight - (btnSpr[0].destRect.height + 10);

  //make copies of buttons, then adjust 'em
  btnSpr.push_back(btnSpr.back());
  btnSpr.back().srcRect.y += btnSpr.back().srcRect.height;
  btnSpr.push_back(btnSpr.back());
  btnSpr.back().srcRect.y += btnSpr.back().srcRect.height;

  menu.AddButton(btnSpr[0], btnSpr[1], btnSpr[2], btnSpr[0].destRect, GSPMessage(RTEXTSCENE, 1));

  GSPRect btnRect = btnSpr[0].destRect;
  btnRect.moveBy(vec2f{10.0f, 5.0f});
  menuText.setRect(btnRect);
}

TextScene::~TextScene() {
  gMessageHandler->RemoveRecipient(RTEXTSCENE);
  gMessageHandler->RemoveRecipient(RTEXTMENU);
}

Scene* TextScene::update(float dt) {
  menu.Update();
  messageBox.processQueue();

  if(messageBox.acceptedValue) { return new TitleScene(store); }

  return this;
}

void TextScene::draw() {
  bg.draw();
  textBox.draw();
  text.draw();
  menu.draw();
  menuText.draw();
}
