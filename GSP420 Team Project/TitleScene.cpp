#include "TitleScene.h"
#include "GameplayScene.h"
#include "MessageHandler.h"
#include "InputManager.h"
#include "SharedStore.h"

TitleScene::TitleScene(SharedStore* store) :
	Scene(store),
	font(L"Ariel"),
	staticText(L"Title Sprite Here", &font), //replace w/ sprite!
	bgtex(L"Texture/ColtonTitleBackground.png"), //replace
	snd("SFX/button-37.mp3"),
	song("BGM/Undaunted.mp3"),
	menuBorder(L"Texture/MenuBorder.png")
{
	gMessageHandler->AddRecipient(&menu, RTESTMENU);
	gMessageHandler->AddRecipient(&messageBox, RSCENE);

	font.setColor(D2D1::ColorF(1, 1)); //black
	font.setSize(40.0f);

	staticText.setRect(GSPRect(420.f, 60.f, 600.f, 200.f));
	batch.addRO(&staticText);
	staticText.z = 0;

	plane.setTexture(bgtex);
	batch.addRO(&plane);
	plane.z = -100;

	mainMenuBorder.setBitmap(menuBorder);
	mainMenuBorder.destRect = mainMenuBorder.srcRect;
	mainMenuBorder.destRect.width *= 0.6f;
	mainMenuBorder.destRect.height -= 10;
	mainMenuBorder.destRect.x = store->screenWidth / 3 + 13;
	mainMenuBorder.destRect.y = 172;
	mainMenuBorder.z = -50;
	batch.addRO(&mainMenuBorder);

	Texture buttons(L"Texture/buttons.png");
	std::vector<Sprite> btnSpr;

	//config first button; button textures are three buttons tiled one above another
	btnSpr.emplace_back();
	btnSpr[0].setBitmap(buttons);
	btnSpr[0].srcRect.height /= 3;

	btnSpr[0].destRect = btnSpr[0].srcRect;
	btnSpr[0].destRect.height *= 0.8;
	btnSpr[0].destRect.x = (store->screenWidth) / 2 - btnSpr[0].srcRect.width/2;
	btnSpr[0].destRect.y = 200;

	//make copies of buttons, then adjust 'em
	btnSpr.push_back(btnSpr[0]);
	btnSpr.back().srcRect.y += btnSpr.back().srcRect.height;
	btnSpr.push_back(btnSpr.back());
	btnSpr.back().srcRect.y += btnSpr.back().srcRect.height;

	//adjust messages!
	menu.AddButton(btnSpr[0], btnSpr[1], btnSpr[2], btnSpr[0].destRect, GSPMessage(RSCENE, 1));
	//move destRect of all three sprites, then add next button; do so twice
	for (auto& spr : btnSpr) { spr.destRect.y += spr.destRect.height + 20; }
	menu.AddButton(btnSpr[0], btnSpr[1], btnSpr[2], btnSpr[0].destRect, GSPMessage(RSCENE, 2));
	for (auto& spr : btnSpr) { spr.destRect.y += spr.destRect.height + 20; }
	menu.AddButton(btnSpr[0], btnSpr[1], btnSpr[2], btnSpr[0].destRect, GSPMessage(RSCENE, 3));
	for (auto& spr : btnSpr) { spr.destRect.y += spr.destRect.height + 20; }
	menu.AddButton(btnSpr[0], btnSpr[1], btnSpr[2], btnSpr[0].destRect, GSPMessage(RSCENE, 4));
	batch.addRO(&menu);

	menuLabels.emplace_back(L"Start Game", &font);
	menuLabels.emplace_back(L"Highscores", &font);
	menuLabels.emplace_back(L"Credits", &font);
	menuLabels.emplace_back(L"Exit Game", &font);

	auto rect = btnSpr[0].destRect;
	rect.y += 10 - (4* (btnSpr[0].destRect.height + 20));
	for (size_t i = 0; i < menuLabels.size(); i++) {
		rect.y += btnSpr[0].destRect.height + 20;
		menuLabels[i].setRect(rect);
		batch.addRO(&menuLabels[i]);
	}
}

TitleScene::~TitleScene() {
	gMessageHandler->RemoveRecipient(RTESTMENU); //doubt this is needed
	gMessageHandler->RemoveRecipient(RSCENE); //don't think this one is either
}

Scene* TitleScene::update(float dt) {
	menu.Update();
	messageBox.processQueue();

	if (store->input.IsKeyPressed(InputManager::KEY_ESC)) { return nullptr; } //quit game!

	SwapScene = messageBox.acceptedValue;
	
	//check if we need to swap scenes, return self if not
	switch (SwapScene)
	{
	case 0: //no buttons pressed
		return this;

	case 1: //move to Game scene
		return new GameplayScene(store); //placeholder

	case 2: //move to Highscore scene
		; //placeholder

	case 3: //move to Credits scene
    ; //placeholder

	case 4: //exit
		return nullptr;

	default:
		//fix value, then return
		SwapScene = 0;
		return this;
	}
}

void TitleScene::draw() {
	batch.draw();
}