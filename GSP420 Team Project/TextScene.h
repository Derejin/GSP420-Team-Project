#pragma once
#include "Scene.h"
#include "Texture.h"
#include "Plane.h"
#include "Sprite.h"
#include "Font.h"
#include "Text.h"
#include "TitleSceneMessageBox.h"

//This scene serves for the credits scene and the instructions scene.
//When it loads the contents fo the file indicated by store->textFile
//and it then displays that text to the user.

class TextScene : public Scene {
public:
  TextScene(SharedStore* store);
  ~TextScene();
  Scene* update(float dt) override;
  void draw() override;

private:
  Texture bgTex;
  Texture black;
  Font font;
  Font menufont;

  Plane bg;
  Sprite textBox;
  Text text;
  Text menuText;

  float timer;
  float SONG_VOLUME = 1.0f;

  TitleSceneMessageBox messageBox;

};
