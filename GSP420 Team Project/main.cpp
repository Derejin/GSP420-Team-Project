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

#include "GSPWindow.h"
#include "Graphics.h"
#include "Text.h"
#include "Font.h"
#include "InputManager.h"
#include "Sprite.h"
#include "MessageHandler.h"
#include "MenuManager.h"
#include "Stella_temp.h"
#include "Plane.h"

//main function - throws error if window fails
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
  GSPWindow gameWindow(L"Testing Window", 1080, 600);
  Graphics gfx(gameWindow);
  InputManager input(gameWindow);
  
  Font font(L"Arial");
  font.setColor(D2D1::ColorF(0,1));
  font.setSize(40.0f);
  Text text(L"Example of Text!", &font);
  text.setRect(D2D1::RectF(100.f, 100.f, 300.f, 100.f));

  Stella stella;

  Texture bgtex(L"tilesetOpenGameBackground_3.png");

  Plane plane;
  plane.setTexture(bgtex);

  while(gameWindow.update()) {
	  input.ReadFrame();
    if(input.IsKeyPressed(InputManager::KEY_ESC)) { break; }

    if(input.IsKeyPressed(InputManager::KEY_DASH)) { stella.update(); }

    //plane.srcRect.x++; //this is busted. I'll fix it. -rb
	  
	  gfx.startDraw();
    plane.draw();
	  stella.draw();
    text.draw();
    gfx.endDraw();
  }

	return 0;
}

