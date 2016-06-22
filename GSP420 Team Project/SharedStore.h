#pragma once
#include "GSPWindow.h"
#include "Graphics.h"
#include "InputManager.h"
#include "Audio.h"
#include "GSPMessage.h"
#include <random>
#include <memory>
#include <string>

struct SharedStore {
  SharedStore();

  //the order of these declarations is important.
  //please do not rearrange them.
  
  //misc data
  const int screenWidth = 1080;
  const int screenHeight = 600;

  const float START_SPEED = 400.0f;
  const float MAX_SPEED = 1500.0f;
  const float DASH_SPEED = 2000.0f;

  RClass msgTgt = RNONE;
  float speed;
  float time = 0;

  int score = 0;

  //systems
  GSPWindow window;
  Graphics gfx;
  InputManager input;
  Audio audio;

  //tools
  std::mt19937 rng;
  std::unique_ptr<Song> bgm;
  std::string songPath;
  float songBaseVol;
  float oldBaseVol;
  std::wstring textFile;

};

