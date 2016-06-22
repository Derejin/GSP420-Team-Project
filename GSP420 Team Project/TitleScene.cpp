#include "TitleScene.h"
#include "GameplayScene.h"
#include "MessageHandler.h"
#include "InputManager.h"
#include "SharedStore.h"
#include "TextScene.h"
#include "High_Score.h"

TitleScene::TitleScene(SharedStore* store) :
	Scene(store),
	font(L"Ariel"),
	staticText(L"Run, Man, Run!", &font),
	bgtex(L"Texture/ColtonTitleBackground.png"),
	snd("SFX/button-37.mp3"),
	menuBorder(L"Texture/MenuBorder.png")
{
	store->oldBaseVol = store->songBaseVol;
	store->songBaseVol = 1.0f;
	store->songPath = "BGM/Undaunted.mp3";

	gMessageHandler->AddRecipient(&menu, RTITLEMENU);
	store->msgTgt = RTITLEMENU;
	gMessageHandler->AddRecipient(&messageBox, RTITLESCENE);

	font.setColor(D2D1::ColorF(1, 1)); //black
	font.setSize(39.0f);

	staticText.setRect(GSPRect(410.f, 60.f, 600.f, 200.f));
	batch.addRO(&staticText);
	staticText.z = 0;

	plane.setTexture(bgtex);
	batch.addRO(&plane);
	plane.z = -100;

	mainMenuBorder.setBitmap(menuBorder);
	mainMenuBorder.destRect = mainMenuBorder.srcRect;
	mainMenuBorder.destRect.width *= 0.6f;
	mainMenuBorder.destRect.height -= 10;
	mainMenuBorder.destRect.x = float(store->screenWidth / 3 + 15);
	mainMenuBorder.destRect.y = 172;
	mainMenuBorder.z = -50;
	batch.addRO(&mainMenuBorder);

	titleBorder.setBitmap(menuBorder);
	titleBorder.destRect = titleBorder.srcRect;
	titleBorder.destRect.width *= 0.6f;
	titleBorder.destRect.height /= 7;
	titleBorder.destRect.x = float(store->screenWidth / 3 + 18);
	titleBorder.destRect.y = 55;
	titleBorder.z = -45;
	batch.addRO(&titleBorder);

	Texture buttons(L"Texture/buttons.png");
	std::vector<Sprite> btnSpr;

	//config first button; button textures are three buttons tiled one above another
	btnSpr.emplace_back();
	btnSpr[0].setBitmap(buttons);
	btnSpr[0].srcRect.height /= 3;

	btnSpr[0].destRect = btnSpr[0].srcRect;
	btnSpr[0].destRect.height *= 0.6f;
	btnSpr[0].destRect.x = (store->screenWidth) / 2 - btnSpr[0].srcRect.width/2;
	btnSpr[0].destRect.y = 200;

	//make copies of buttons, then adjust 'em
	btnSpr.push_back(btnSpr[0]);
	btnSpr.back().srcRect.y += btnSpr.back().srcRect.height;
	btnSpr.push_back(btnSpr.back());
	btnSpr.back().srcRect.y += btnSpr.back().srcRect.height;

	//adjust messages!
	menu.AddButton(btnSpr[0], btnSpr[1], btnSpr[2], btnSpr[0].destRect, GSPMessage(RTITLESCENE, 1));
	//move destRect of all three sprites, then add next button; do so thrice
	for (auto& spr : btnSpr) { spr.destRect.y += spr.destRect.height + 20; }
	menu.AddButton(btnSpr[0], btnSpr[1], btnSpr[2], btnSpr[0].destRect, GSPMessage(RTITLESCENE, 2));
	for (auto& spr : btnSpr) { spr.destRect.y += spr.destRect.height + 20; }
	menu.AddButton(btnSpr[0], btnSpr[1], btnSpr[2], btnSpr[0].destRect, GSPMessage(RTITLESCENE, 3));
	for (auto& spr : btnSpr) { spr.destRect.y += spr.destRect.height + 20; }
	menu.AddButton(btnSpr[0], btnSpr[1], btnSpr[2], btnSpr[0].destRect, GSPMessage(RTITLESCENE, 4));
	for (auto& spr : btnSpr) { spr.destRect.y += spr.destRect.height + 20; }
	menu.AddButton(btnSpr[0], btnSpr[1], btnSpr[2], btnSpr[0].destRect, GSPMessage(RTITLESCENE, 5));
	batch.addRO(&menu);

	menuLabels.emplace_back(L"Start Game", &font);
	menuLabels.emplace_back(L"Instructions", &font);
	menuLabels.emplace_back(L"Highscores", &font);
	menuLabels.emplace_back(L"Credits", &font);
	menuLabels.emplace_back(L"Exit Game", &font);

	//set the menuLabel's coordinate values manually, so they're centered
	auto rect = btnSpr[0].destRect;
	rect.y += 10 - (5 * (btnSpr[0].destRect.height + 20));

	//for StartGame
	rect.x += 3; 
	rect.y += btnSpr[0].destRect.height + 15;
	menuLabels[0].setRect(rect);
	batch.addRO(&menuLabels[0]);

	//for Instructions
	rect.x -= 3;
	rect.y += btnSpr[0].destRect.height + 20;
	menuLabels[1].setRect(rect);
	batch.addRO(&menuLabels[1]);

	//for Highscores
	rect.x += 5;
	rect.y += btnSpr[0].destRect.height + 20;
	menuLabels[2].setRect(rect);
	batch.addRO(&menuLabels[2]);

	//for Credits
	rect.x += 35;
	rect.y += btnSpr[0].destRect.height + 20;
	menuLabels[3].setRect(rect);
	batch.addRO(&menuLabels[3]);

	//for Exit
	rect.x -= 25;
	rect.y += btnSpr[0].destRect.height + 20;
	menuLabels[4].setRect(rect);
	batch.addRO(&menuLabels[4]);
}

TitleScene::~TitleScene() {
	gMessageHandler->RemoveRecipient(RTITLEMENU); //doubt this is needed
	gMessageHandler->RemoveRecipient(RTITLESCENE); //don't think this one is either
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
		break;

	case 1: //move to Game scene
		return new GameplayScene(store);
		break;

	case 2: //move to Instructions scene
		store->textFile = L"instructions.txt";
		return new TextScene(store);
		break;

	case 3: //move to Highscore scene
		return new High_Score(store);
		break;

	case 4: //move to Credits scene
		store->textFile = L"credits.txt";
		return new TextScene(store);
		break;

	case 5: //exit
		return nullptr;
		break;

	default:
		//fix value, then return
		SwapScene = 0;
		return this;
		break;
	}
}

void TitleScene::draw() {
	batch.draw();
}