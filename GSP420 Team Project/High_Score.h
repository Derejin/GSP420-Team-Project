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

class High_Score : public Scene {
public:
	High_Score(SharedStore* store);
	~High_Score();
	Scene* update(float dt) override;
	void draw() override;

private:
	Texture bgTex;
	Texture black;
	Font font;
	Font menufont;

	Plane bg;
	Sprite textBox;
	Text scoreText;
	Text dateText;
	Text menuText;

	float SONG_VOLUME = 1.0f;

	TitleSceneMessageBox messageBox;

};