//InputManager class, for initializing DirectInput in order to receive input
//from users

//created 5/19/2016, 9:38 PM, by Derek Baumgartner
//based upon Rastertek tutorial at http://www.rastertek.com/dx11tut13.html

//updated 5/20/2016, 11:28 PM by Derek Baumgartner,
//to add required comments for DirectInput

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include "InputManager.h"
#include <assert.h>


//parameterized constructor - only constructor that should be used for this class
//sets up DirectInput, and sets up connected mouse+keyboard
InputManager::InputManager(GSPWindow& win)
{
	/*tested setting mouse with this block - resulted in very buggy behavior*/
	//set mouse position to top of window
	RECT rect = { 0 };
	GetWindowRect(win.getHandle(), &rect);
	SetCursorPos(rect.right - win.WIDTH, rect.bottom - win.HEIGHT);
	

	//zero out pointers
	input_directInput = 0;
	input_keyboard = 0;
	input_mouse = 0;

	//prepare result
	HRESULT result;

	//store screen size, for positioning the mouse cursor
	input_screenWidth = win.WIDTH;
	input_screenHeight = win.HEIGHT;

	//initialize mouse location
	input_MousePos.X = 0;
	input_MousePos.Y = 0;

	//initialize DirectInput
	result = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, 
		(void**)&input_directInput, NULL);
	//assert it worked properly
	assert(!FAILED(result) && "DirectInput: Initialization Failed");


	//KEYBOARD SETUP//
	//initialize the keyboard
	result = input_directInput->CreateDevice(GUID_SysKeyboard, &input_keyboard, NULL);
	//assert it worked properly
	assert(!FAILED(result) && "DirectInput: Keyboard Initialization Failed");

	//then set keyboard data format
	result = input_keyboard->SetDataFormat(&c_dfDIKeyboard);
	//assert it worked properly
	assert(!FAILED(result) && "DirectInput: Keyboard Format Initialization Failed");

	//set keyboard cooperative level, so keyboard won't share with other programs
	//change to DISCL_NONEXCLUSIVE if you want to share
	result = input_keyboard->SetCooperativeLevel(win.getHandle(), DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	//assert it worked properly
	assert(!FAILED(result) && "DirectInput: Keyboard Set Cooperative Level Failed");

	//now acquire keyboard for use with DirectInput
	result = input_keyboard->Acquire();
	//and assert it worked properly
	assert(!FAILED(result) && "DirectInput: Keyboard Acquire Failed");

	//MOUSE SETUP//
	//initialize mouse
	result = input_directInput->CreateDevice(GUID_SysMouse, &input_mouse, NULL);
	//assert it worked properly
	assert(!FAILED(result) && "DirectInput: Mouse Initialization Failed");

	//set mouse data format
	result = input_mouse->SetDataFormat(&c_dfDIMouse);
	//assert it worked properly
	assert(!FAILED(result) && "DirectInput: Mouse Format Initialization Failed");

	//mouse cooperative level set to nonexclusive, 
	//so it can move in and out of the game window at will
	//set to DISCL_EXCLUSIVE to lock to the window
	result = input_mouse->SetCooperativeLevel(win.getHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	//assert it worked properly
	assert(!FAILED(result) && "DirectInput: Mouse Set Cooperative Level Failed");

	//now acquire mouse for use with DirectInput
	result = input_mouse->Acquire();
	//assert it worked properly
	assert(!FAILED(result) && "DirectInput: Mouse Acquire Failed");
}

//destructor - releases the keyboard, the mouse, and DirectInput
InputManager::~InputManager()
{
	//release mouse, if it's connected
	if (input_mouse)
	{
		//unacquire the mouse, release it from directinput, then set the pointer to 0
		input_mouse->Unacquire();
		input_mouse->Release();
		input_mouse = 0;
	}

	//release keyboard, if it's connected
	if (input_keyboard)
	{
		//unacquire keyboard, release it from directinput, then set the pointer to 0
		input_keyboard->Unacquire();
		input_keyboard->Release();
		input_keyboard = 0;
	}

	//release main interface to DirectInput
	if (input_directInput)
	{
		//release interface, then set pointer to 0
		input_directInput->Release();
		input_directInput = 0;
	}

	return;
}

bool InputManager::ReadFrame()
{
	//result, for asserts
	bool result;

	//copy current keyboard and mouse states into previous states, to save previous frame states
	prev_keyboardState = input_keyboardState;
	prev_mouseState = input_mouseState;

	//copy current mousePos into the previous, as well
	prev_MousePos = input_MousePos;

	//read keyboard state
	result = ReadKeyboard();
	assert(result && "Keyboard Read Failed");

	//read mouse state
	result = ReadMouse();
	assert(result && "Mouse Read Failed");

	//process changes in mouse+keyboard
	ProcessInput();

	//return true, for success
	return true;
}

//reads changes in keyboard
bool InputManager::ReadKeyboard()
{
	//result, for checking success/failure
	HRESULT result;

	//read keyboard
	result = input_keyboard->GetDeviceState(sizeof(input_keyboardState), (LPVOID)&input_keyboardState);

	//if failed, attempt to (re)acquire keyboard
	if (FAILED(result))
	{
		//attempt reacquire
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			input_keyboard->Acquire();
		}
		//if reacquire fails, return false
		else
		{
			return false;
		}
	}
	
	return true;
}

//ReadMouse, for reading changes in mouse - changes, not actual position! (i.e. "mouse moved x and y,"
//not "mouse is at point (x, y)"
bool InputManager::ReadMouse()
{
	//result, for checking success/failure
	HRESULT result;

	//read the mouse
	result = input_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&input_mouseState);
	//if failed, attempt to (re)acquire
	if (FAILED(result))
	{
		//attempt reacquire
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			input_mouse->Acquire();
		}
		//if acquire failed, return false
		else
		{
			return false;
		}
	}

	return true;
}

//ProcessInput, for updating mouse position and checking relevant keypresses
//EXPAND THIS FUNCTION with key press checks, to add functionality!
void InputManager::ProcessInput()
{
	//update location of mouse cursor based on mouse changes
	input_MousePos.X += input_mouseState.lX;
	input_MousePos.Y += input_mouseState.lY;

	//bound the mouse inside the window
	if (input_MousePos.X < 0) { input_MousePos.X = 0; }
	if (input_MousePos.Y < 0) { input_MousePos.Y = 0; }
	if (input_MousePos.X > input_screenWidth) { input_MousePos.X = input_screenWidth; }
	if (input_MousePos.Y > input_screenHeight) { input_MousePos.Y = input_screenHeight; }

	//keyboard checks here? likely just app-layer stuff instead


	return;
}

//returns true if the mouse moved this frame
bool InputManager::MouseMoved()
{
	if (input_MousePos == prev_MousePos)
		return false;
	else
		return true;
}

//KEYBOARD CHECKING FUNCTIONS//
//If the passed-in key is held down, will return true
bool InputManager::IsKeyPressed(InputKey key)
{
	//bitwise check, returns true if pressed down and false if not
	return input_keyboardState[keyMap[key]] && 0x80;
}

//if the passed-in key is initially pressed in this frame, will return true
bool InputManager::IsKeyTriggered(InputKey key)
{
	//if the key wasn't pressed in the previous frame, but is in this frame
	if (!(prev_keyboardState[keyMap[key]] && 0x80) && IsKeyPressed(key))
		return true;
	else
		return false;
}

//if the passed-in key was released this frame, will return true
bool InputManager::IsKeyReleased(InputKey key)
{
	//if the key was pressed in the previous frame, but not in this frame
	if ((prev_keyboardState[keyMap[key]] && 0x80) && !IsKeyPressed(key))
		return true;
	else
		return false;
}

//MOUSE CHECKING FUNCTIONS//
//if the passed-in mousebutton is held down, will return true
bool InputManager::IsMousePressed(InputMouse button)
{
	//bitwise check, returns true if pressed down and false if not
	return input_mouseState.rgbButtons[button] && 0x80;
}

//if the passed-in mousebutton is initially pressed in this frame, will return true
bool InputManager::IsMouseTriggered(InputMouse button)
{
	//if the mousebutton wasn't pressed in the previous frame, but is in this frame
	if (!(prev_mouseState.rgbButtons[button] && 0x80) && IsMousePressed(button))
		return true;
	else
		return false;
}

//if the passed-in mousebutton is released this frame, will return true
bool InputManager::IsMouseReleased(InputMouse button)
{
	//if the mousebutton was pressed in the previous frame, but isn't in this frame
	if ((prev_mouseState.rgbButtons[button] && 0x80) && !IsMousePressed(button))
		return true;
	else
		return false;
}

//getter to return the exact location of the mouse cursor, as a Point struct
Point InputManager::GetMouseLocation()
{
	return input_MousePos;
}