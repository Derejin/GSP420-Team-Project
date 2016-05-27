//InputManager class, for initializing DirectInput in order to receive input
//from users

//created 5/19/2016, 9:21 PM, by Derek Baumgartner
//based upon Rastertek tutorial at http://www.rastertek.com/dx11tut13.html

//updated 5/20/2016, 11:38 by Derek,
//to streamline KeyInput enum and fix the directinput version declaration

#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <array>
#include "GSPWindow.h"

//struct Point, for simultaneously holding an X and a Y coordinate
struct Point
{
	int X;
	int Y;

	Point() {
		X = 0;
		Y = 0;
	}

	Point(int x, int y) {
		X = x;
		Y = y;
	}

	//check if equal to another point
	bool operator== (const Point& other) {
		if (X == other.X && Y == other.Y)
			return true;
		else
			return false;
	}
};

//number of keys to check for
const int INPUT_NUM_KEYS = 8;

class InputManager
{
private:
	IDirectInput8* input_directInput; // pointer to the IDirectInput8 instance, for managing DirectInput
	IDirectInputDevice8* input_keyboard; // pointer to the keyboard
	IDirectInputDevice8* input_mouse; // pointer to the mouse

	//used to translate up InputKey values to the proper DirectInput values for the keyboard keys
	DWORD keyMap[INPUT_NUM_KEYS] = { 
		//set the Direct Input Key values here to translate from the ENUM "InputKey"
		//must have the same number of elements as InputKey
		DIK_ESCAPE, 
		DIK_RETURN,
		DIK_X,
		DIK_Z,
		DIK_W,
		DIK_UP,
		DIK_S,
		DIK_DOWN
	};

	//for reading current and previous keyboard states!
	std::array<char, 256> input_keyboardState, prev_keyboardState;

	//for reading current and previous mouse states!
	DIMOUSESTATE input_mouseState, prev_mouseState;

	int input_screenWidth, input_screenHeight; //height+width vars, for use with the mouse

											   //mouse position points, for both current and previous frames
	Point input_MousePos, prev_MousePos;

	HWND windowHandle;

	bool ReadKeyboard(); //reads the keyboard. attempts to reacquire if something goes wrong,
						 //otherwise returns true.
	bool ReadMouse(); //reads the mouse. attempts to reacquire if something goes wrong,
					  //otherwise returns true.
	void ProcessInput(); //processes the above input for use by the game (varying by gamestate).

public:

	InputManager(GSPWindow& win);
	~InputManager();

	//InputKey enumeration, for checking which keystrokes to scan for
	enum InputKey {
		//define desired keystrokes to scan for here 
		//note: the above const int INPUT_NUM_KEYS must be set to the number of elements
		//in this enum!
		KEY_ESC = 0,
		KEY_ENTER,
		KEY_JUMP,
		KEY_DASH,
		KEY_W,
		KEY_UP,
		KEY_S,
		KEY_DOWN
	};

	//InputMouse enumeration, for checking which mouse button to scan for
	enum InputMouse {
		MOUSE_LEFT,
		MOUSE_RIGHT,
		MOUSE_THREE,
		MOUSE_FOUR
	};

	bool ReadFrame(); //runs private Read+Process functions to read the current frame of the game

	//returns true if the mouse moved
	bool MouseMoved();

	//keyboard checking functions
	bool IsKeyPressed(InputKey key); //for checking if the desired key is pressed down at all
	bool IsKeyTriggered(InputKey key); //for checking if the desired key was initially triggered this frame
	bool IsKeyReleased(InputKey key); //for checking if the desired key was released this frame

	//mouse button checking functions
	bool IsMousePressed(InputMouse button);
	bool IsMouseTriggered(InputMouse button);
	bool IsMouseReleased(InputMouse button);

	//Getter for input_MousePos
	Point GetMouseLocation();

	//Getter for mouse delta
	Point GetMouseDelta();
};
