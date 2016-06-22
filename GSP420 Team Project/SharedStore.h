#pragma once
#include "GSPWindow.h"
#include "Graphics.h"
#include "InputManager.h"
#include "Audio.h"
#include "GSPMessage.h"
#include <random>
#include <memory>
#include <string>

//This struct encapsulates data and systems that do not belong to any specific scene
//it serves as an access point for shared resources and data that multiple scenes may
//want access to.

struct SharedStore {
  SharedStore();

  //the order of these declarations is important.
  //please do not rearrange them.
  
  const int screenWidth = 1080;
  const int screenHeight = 600;

  //systems
  GSPWindow window;
  Graphics gfx;
  InputManager input;
  Audio audio;

  //settings for gameplay scene
  const float START_SPEED = 400.0f;
  const float MAX_SPEED = 1500.0f;
  const float DASH_SPEED = 2000.0f;

  //active data for gameplay scene
  float speed;
  float time = 0;
  int score = 0;

  //scenes should set this value to match their menu object
  //the main control loop will send messages to this recipient
  //based on input recieved in order to enable menu processing
  RClass msgTgt = RNONE;

  //random number engine - seeded in constructor
  //to be used with distributions provided by <random>
  //refer to http://www.cplusplus.com/reference/random/
  std::mt19937 rng;

  //shared song instance - you shouldn't really need more than one
  //song playing at a time, so this is placed here to facilitate
  //smooth transitioning with fade out/in
  std::unique_ptr<Song> bgm;

  //in order to make use of smooth music transitions Scene constructors
  //should set these three values:
    //the song to play for the new scene
  std::string songPath;
    //the volume to play the song at, with 1.0f being 100%
  float songBaseVol;
    //please copy 'songBaseVol' into this value prior to setting 'songBaseVol'
  float oldBaseVol;
    //refer to any implemented Scene derivative for examples

  //path of text file to open for TextScene class
  //when TextScene constructs it looks for the file indicated here
  //and attempts to read its contents in order to display them
  std::wstring textFile;

};

