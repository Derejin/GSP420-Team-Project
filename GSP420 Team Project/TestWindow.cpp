//exists to test GSPWindow functionality.
//created 5/17/2016, 6:45 PM, by Derek Baumgartner 
//modified 5/17 16:42PST by Richard
//- removed exception handling clause and consolidated into main()
//- added test of update loop
//modified 5/17 17:16PST by Richard
//- added test of Graphics class
//modified 5/17 18:02PST by Richard
//- added Texture junk

#include "GSPWindow.h"
#include "Graphics.h"
#include "Texture.h"

//set screen width and height here
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 600;

//main function - throws error if window fails
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
  GSPWindow gameWindow(L"Testing Window", SCREEN_WIDTH, SCREEN_HEIGHT);
  Graphics gfx(gameWindow);

  //nothing to do with this yet, but it appears to be loading correctly
  Texture test(L"test image.png");

  while(gameWindow.update()) {
    gfx.startDraw();
    //draw calls go here
    gfx.endDraw();
  }

	return 0;
}

