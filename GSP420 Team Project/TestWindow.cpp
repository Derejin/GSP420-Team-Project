//exists to test GSPWindow functionality.
//created 5/17/2016, 6:45 PM, by Derek Baumgartner 
//modified 5/17 4:42PST by Richard
//- removed exception handling clause and consolidated into main()
//- added test of update loop

#include "GSPWindow.h"
#include <iostream>

//set screen width and height here
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 600;

//main function - throws error if window fails
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
  GSPWindow gameWindow(L"Testing Window", SCREEN_WIDTH, SCREEN_HEIGHT);

  while(gameWindow.update()) {
    //wheeee!
  }

	return 0;
}