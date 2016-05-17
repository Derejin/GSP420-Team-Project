#include "GSPWindow.h"
#include <iostream>

//created 5/17/2016, 6:45 PM, by Derek Baumgartner 
//exists to test GSPWindow functionality.

//set screen width and height here
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 600;

//application function
void WindowTestApp(){
	//currently only for testing
	GSPWindow gameWindow(L"Testing Window", SCREEN_WIDTH, SCREEN_HEIGHT);

	//sleep for 2 secs, to see if window size is correct
	Sleep(2000);
}

//main function - throws error if window fails
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
	try { WindowTestApp(); }
	catch (std::exception& e) { MessageBoxA(NULL, e.what(), "Error", MB_OK | MB_ICONERROR); }
	return 0;
}