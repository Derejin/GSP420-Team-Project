//GSPWindow class, to set up the game window and provide the window handle (HWND) object
//for D2D and DirectInput to use.

//created 5/17/2016, 6:00 PM, by Derek Baumgartner
//modified 5/17, 16:45PST by Richard
//- added some usage commenting for update()

#pragma once
#include <Windows.h>
#include <string>
#include <assert.h>


//This class, with definitions, requires UNICODE to function.
//For Visual Studio, this means Project Properties->Configuration Properties->General->Character Set
//is set to "Use Unicode Character Set".

class GSPWindow {
public:
	GSPWindow(std::wstring windowTitle, int width, int height);
	~GSPWindow();

	bool update(); //for reading messages - returns false to signal 'quit', otherwise returns true
	HWND getHandle() const; //for returning handle

	const int WIDTH;
	const int HEIGHT;

private:
  HWND handle;
  std::wstring className; //for containing the name of the created window

};