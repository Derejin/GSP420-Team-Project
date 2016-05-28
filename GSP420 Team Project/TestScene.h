#pragma once
#include "Plane.h"
#include "DepthBatch.h"
#include "MenuManager.h"
#include "Stella_temp.h"
#include "Text.h"
#include "Font.h"
#include "Sprite.h"

class InputManager;

class TestScene {
public:
  TestScene(InputManager& inputMgr, int screenWidth, int screenHeight);
  bool update();
  void draw();

private:
  Font font;
  Text staticText;
  Stella stella;
  Texture bgtex;
  Plane plane;
  DepthBatch batch;
  MenuManager menu;
  std::vector<Text> menuLabels;

  InputManager* input;

};