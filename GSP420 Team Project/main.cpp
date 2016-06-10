//exists to test GSPWindow functionality.
//created 5/17/2016, 6:45 PM, by Derek Baumgartner 
//modified 5/17 16:42PST by Richard
//- removed exception handling clause and consolidated into main()
//- added test of update loop
//modified 5/17 17:16PST by Richard
//- added test of Graphics class
//modified 5/17 18:02PST by Richard
//- added Texture junk
//modified 5/20 14:24PST by Richard
//- changed file name to main.cpp, testing font functions
//modified 5/20 11:49EST by Derek
//-adding InputManager and InputManager testing - testing not working yet, key input not
//seemingly being read.
//modified 5/21 0:19EST by Derek
//-testing of input was working, but rectangle wasn't being set properly to 
//see the changes caused by pressing Z.
//modified 5/23 4:32EST by Derek
//to add tests for MenuManager, MenuButton, and the Messaging System
// however, bug encountered when attempting to instantiate MenuManager. Pushing as separate branch
// to see help from Richard.
//edited 5/26/2016 at 11:33 AM EST by Derek
//to update MenuButton+MenuManager to GSPRect and attempt fixing an issue with buttons failing to draw properly

#include "GSPWindow.h"
#include "Graphics.h"
#include "InputManager.h"
#include "MessageHandler.h"
#include "TestScene.h"
#include "Audio.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
  GSPWindow gameWindow(L"Testing Window", 1080, 600);
  Graphics gfx(gameWindow);
  InputManager input(gameWindow);
  Audio audio;
  gMessageHandler->Instantiate();

  TestScene scene(input, gameWindow.WIDTH, gameWindow.HEIGHT);

  while(gameWindow.update()) {
	  input.ReadFrame();

    if(scene.update()) {
  	  gfx.startDraw();
      scene.draw();
      gfx.endDraw();
    }
    else {
      break;
    }
  }

	return 0;
}

