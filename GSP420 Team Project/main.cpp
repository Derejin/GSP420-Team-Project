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

//Testing if this works
//Testing number two

#include "GSPWindow.h"
#include "Graphics.h"
#include "Text.h"
#include "Font.h"
#include "InputManager.h"
#include "Sprite.h"


//set screen width and height here
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 600;

//main function - throws error if window fails
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
  GSPWindow gameWindow(L"Testing Window", SCREEN_WIDTH, SCREEN_HEIGHT);
  Graphics gfx(gameWindow);
  InputManager input(HINSTANCE(GetModuleHandle(NULL)), gameWindow.getHandle(), SCREEN_WIDTH, SCREEN_HEIGHT);

  //Bitmap objects serve as handles and information sources for loaded textures
  Texture tex(L"stella_walk_2.png");

  Sprite stellaspr;
  stellaspr.setBitmap(tex); 
  stellaspr.destRect = stellaspr.srcRect;
  stellaspr.opacity = 1.0f;
  
  stellaspr.srcWidth = (float)(tex.getWidth() / 4);
  stellaspr.srcHeight = (float)(tex.getHeight() / 8);

  int startx = 0;// starting point for sprite animation for walking
  int endx = tex.getWidth(); //end point for sprite animation walking

  int starty = 256; // this is the front position of the cell I am wanting to use for walking
  int endy = 320; // this is the end position of the cell I am wanting to use for walking
  int walkingSpeed = 3; // walking speed for each tich that the z button is held down

  int tickCount = 0;

  //Stella-specific animation stuff
  const int faceorder[] = { 0, 5, 1, 6, 3, 7, 2, 4 }; //spritesheet was in a weird order and I don't feel like changing it
  int stepFreq = 30;   //how many ticks pass before advancing animation frame
  int turnFreq = 100; //how many ticks pass before changing direction
  int stepCells = 4;  //number of cells in walking loop (horizontal frames)
  int directions = 8; //number of directions represented (vertical frames)

  Font font(L"Arial");
  Text text(L"The herp derpinest.", &font);
  text.setRect(D2D1::RectF(100.f, 100.f, 300.f, 100.f));

  while(gameWindow.update()) {
	//to test input: will check for "Z" (KEY_DASH)
	//and change the text's rectangle
	  //currently not working.
	  input.ReadFrame();

	  tickCount++;

	  //update stella
	  
	  if (input.IsKeyPressed(InputManager::KEY_DASH)) {
		  text.setRect(D2D1::RectF(200.f, 100.f, 400.f, 300.f));
		  stellaspr.srcRect = (D2D1::RectF(((tickCount % (stepCells  * stepFreq)) / stepFreq) * stellaspr.srcWidth, starty, ((tickCount % (stepCells  * stepFreq)) / stepFreq) * stellaspr.srcWidth + stellaspr.srcWidth, endy));
		  stellaspr.destRect = (D2D1::RectF(startx+=walkingSpeed,0, endx+=walkingSpeed, tex.getHeight()));
	  }
	  else {
		  text.setRect(D2D1::RectF(100.f, 100.f, 300.f, 100.f));
	  }
	
	  
	gfx.startDraw();
	text.draw();
	stellaspr.draw();
    gfx.endDraw();
  }

	return 0;
}

