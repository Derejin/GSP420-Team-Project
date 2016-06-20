#pragma once
#include "Plane.h"
#include "DepthBatch.h"
#include "Text.h"
#include "Font.h"
#include "Sprite.h"
#include "Audio.h"
#include "Sound.h"
#include "Scene.h"
#include "TitleSceneMessageBox.h"

class TitleScene : public Scene {
public:
	TitleScene(SharedStore* store);
	~TitleScene();
	Scene* update(float dt) override;
	void draw() override;

private:
	Sound snd;
	//Song song;
	Font font;
	Text staticText;
	Texture bgtex;
	Texture menuBorder;
	Plane plane;
	DepthBatch batch;
	Sprite mainMenuBorder;
	std::vector<Text> menuLabels;

	TitleSceneMessageBox messageBox;

	//which scene to swap to. 
	int SwapScene; //0 means do not swap, 1 means Game, 2 means Highscore, 3 means Credits, 4 means Quit

};