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

#include "GSPWindow.h"
#include "Graphics.h"
#include "Text.h"
#include "Font.h"

//set screen width and height here
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 600;

//main function - throws error if window fails
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
  GSPWindow gameWindow(L"Testing Window", SCREEN_WIDTH, SCREEN_HEIGHT);
  Graphics gfx(gameWindow);

  Font font(L"Arial");
  Text text(L"The herp derpinest.", &font);
  text.setRect(D2D1::RectF(100.f, 100.f, 300.f, 100.f));

  while(gameWindow.update()) {
    gfx.startDraw();
    text.draw();
    gfx.endDraw();
  }

	return 0;
}

