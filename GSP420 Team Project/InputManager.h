//InputManager class, for initializing DirectInput in order to receive input
//from users

//created 5/19/2016, 9:21 PM, by Derek Baumgartner
//based upon Rastertek tutorial at http://www.rastertek.com/dx11tut13.html

#pragma once
#include <assert.h>

//directinput version declaration
#define DIRECTINPUT_VERSION0x0800

//linker requirements
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

//DirectInput header
#include <dinput.h>

//struct Point, for simultaneously holding an X and a Y coordinate
struct Point
{
	int X;
	int Y;
};

//number of keys to check for
const int INPUT_NUM_KEYS = 4;

class InputManager
{
private:
	//do not use default constructor - use parameterized instead
	//default constructor placed as private to prevent misuse
	InputManager();

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
		DIK_Z
	};

	unsigned char input_keyboardState[256]; //holds the keyboard state(s)!
	DIMOUSESTATE input_mouseState; //holds the mouse state!

	int input_screenWidth, input_screenHeight; //height+width vars, for use with the mouse
	Point input_MousePos; //mouse positions, for use with the mouse graphics

	bool ReadKeyboard(); //reads the keyboard. attempts to reacquire if something goes wrong,
						 //otherwise returns true.
	bool ReadMouse(); //reads the mouse. attempts to reacquire if something goes wrong,
					  //otherwise returns true.
	void ProcessInput(); //processes the above input for use by the game (varying by gamestate).

public:
	//parameterized constructor. do not use default! (privatized default to help deal with that)
	InputManager(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight);

	//destructor
	~InputManager();

	//InputKey enumeration, for checking which keystrokes to scan for
	enum InputKey {
		//define desired keystrokes to scan for here 
		//note: the above const int INPUT_NUM_KEYS must be set to the number of elements
		//in this array!
		KEY_ESC = 0,
		KEY_ENTER = 1,
		KEY_JUMP = 2,
		KEY_DASH = 3,
	};

	bool ReadFrame(); //runs ReadKeyboard, ReadMouse, then ProcessInput
						  // in order to read the current frame of the game
	bool IsKeyPressed(InputKey key); //uses a switch to check if the desired key is pressed down

	//returns the Point that contains the mouse coordinates
	//useful for checking mouse position against menu objects
	Point GetMouseLocation();
};
