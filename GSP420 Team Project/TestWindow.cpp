//exists to test GSPWindow functionality.
//created 5/17/2016, 6:45 PM, by Derek Baumgartner 
//modified 5/17 16:42PST by Richard
//- removed exception handling clause and consolidated into main()
//- added test of update loop
//modified 5/17 17:16PST by Richard
//- added test of Graphics class
//modified 5/17 18:02PST by Richard
//- added Texture junk
//modified 5/20 4:39 AM by Derek
//- added test logic for InputManager, updated comments+format+texture testing name
//- error encountered: seeking help from Richard due to InputManager class not instantiating properly
//modified 5/20, 11:30 PM by Derek
//- fixed issue with InputManager construction, updated test to work

#include "GSPWindow.h"
#include "Graphics.h"
#include "Texture.h"
#include "InputManager.h"
#include <iostream>

//set screen width and height here
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 600;

//main function
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
	//window initialization
	GSPWindow gameWindow(L"Testing Window", SCREEN_WIDTH, SCREEN_HEIGHT);

	//graphics initialization
	Graphics gfx(gameWindow);

	//input initialization
	InputManager input((HINSTANCE)GetModuleHandle(NULL), gameWindow.getHandle(), SCREEN_WIDTH, SCREEN_HEIGHT);
	
	//nothing to do with this yet, but it appears to be loading correctly
	Texture testTexture(L"test image.png");

	//add test for input manager here

	while (gameWindow.update()) {
		gfx.startDraw();
		//draw calls go here
		gfx.endDraw();
	}

	return 0;
}

