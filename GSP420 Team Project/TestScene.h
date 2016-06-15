#pragma once
#include "Plane.h"
#include "DepthBatch.h"
#include "Stella_temp.h"
#include "Text.h"
#include "Font.h"
#include "Sprite.h"
#include "Audio.h"
#include "Sound.h"
#include "Scene.h"

class TestScene : public Scene {
public:
  TestScene(SharedStore* store);
  ~TestScene();
  Scene* update(float dt) override;
  void draw() override;

private:
  Sound snd;
  Song song;
  Font font;
  Text staticText;
  Stella stella;
  Texture bgtex;
  Plane plane;
  DepthBatch batch;
  std::vector<Text> menuLabels;

};