#pragma once
#include "GSPWindow.h"
#include "Graphics.h"
#include "InputManager.h"
#include "Audio.h"
#include "GSPMessage.h"

struct SharedStore {
  SharedStore();

  //the order of these declarations is important.
  //please do not rearrange them.
  
  //misc data
  const int screenWidth = 1080;
  const int screenHeight = 600;
  RClass msgTgt = RTESTMENU;

  //systems
  GSPWindow window;
  Graphics gfx;
  InputManager input;
  Audio audio;

};
