#include "High_Score.h"
#include "MessageHandler.h"
#include "SharedStore.h"
#include <fstream>
#include <sstream>
#include <string>
#include "TitleScene.h"

High_Score::High_Score(SharedStore* store) :
	bgTex(L"Texture/ColtonTitleBackground.png"),
	black(L"Texture/Planes/black.png"),
	font(L"Arial"),
	menufont(L"Arial"),
	scoreText(L"", &font),
	dateText(L"", &font),
	menuText(L"Back", &menufont),
	Scene(store)
{
	//adding song information to the store for smooth music transition
	store->oldBaseVol = store->songBaseVol;
	store->songBaseVol = SONG_VOLUME;
	store->songPath = "BGM/Monkeys Spinning Monkeys.mp3";

	//registering the button and the button responder
	gMessageHandler->AddRecipient(&menu, RHIGHSCORE);
	store->msgTgt = RHIGHSCORE;
	gMessageHandler->AddRecipient(&messageBox, RHIGHSCORESCENE);

	//bg
	bg.setTexture(bgTex);

	std::vector<std::wstring> scores(5);
	std::vector<std::wstring> dates(5);

	std::wifstream file("hiscores.txt");
	assert(file && "Failed to open file.");

	for (int i = 0; i < 5; i++) {
		std::getline(file, scores[i]);
		std::getline(file, dates[i]);
	}

	//Set Scores
	std::wstringstream ss;
	for (auto str : scores) {
		ss << str << "\n";
	}
	scoreText.setString(ss.str());
	ss.str(L"");
	for (auto str : dates) {
		ss << str << "\n";
	}
	dateText.setString(ss.str());

	//primary text
	GSPRect textRect(400.0f, 200.0f, 150.0f, 400.0f);
	scoreText.setRect(textRect);
  textRect.x += 200.0f;
	dateText.setRect(textRect);
	
  textRect.x -= 210.0f;
  textRect.width += 170;
  textRect.y -= 10.0f;
  textRect.height = 140.0f;
  textBox.setBitmap(black);
  textBox.destRect = textRect;
  textBox.opacity = 0.8f;

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

	menu.AddButton(btnSpr[0], btnSpr[1], btnSpr[2], btnSpr[0].destRect, GSPMessage(RHIGHSCORESCENE, 1));

	GSPRect btnRect = btnSpr[0].destRect;
	btnRect.moveBy(vec2f{ 10.0f, 5.0f });
	menuText.setRect(btnRect);
}

High_Score::~High_Score() {
	gMessageHandler->RemoveRecipient(RHIGHSCORE);
	gMessageHandler->RemoveRecipient(RHIGHSCORESCENE);
}

Scene* High_Score::update(float dt) {
	menu.Update();
	messageBox.processQueue();

	if (messageBox.acceptedValue) { return new TitleScene(store); }

	return this;
}

void High_Score::draw() {
	bg.draw();
	textBox.draw();
	scoreText.draw();
	dateText.draw();
	menu.draw();
	menuText.draw();
}

