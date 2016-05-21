//created 5/21/2016 at 1:32 AM EST by Derek Baumgartner
//MenuManager class, for managing menus!

#pragma once
#include <vector>
#include "MenuButton.h"

class MenuManager
{
private:

	std::vector<MenuButton> Buttons; //vector array for storing this menu's buttons

	//to be implemented when Message struct created
	//std::vector<Message> MessageQueue; //vector array for storing messages sent to this Menu

	int currentSelection; //currently selected button in the vector array

	//selection incrementation/decrementation functions.
	//these should not run if the mouse moved in the current frame,
	//OR if Buttons.size() <= 1.
	void DecrementSelection();
	void IncrementSelection();

public:

	friend class MenuButton; //allows this class to modify private MenuButton values and call its privatized constructor

	//constructors - both initialize currentSelection to 0
	MenuManager(); //default constructor - runs Buttons.reserve(4) to make room for four buttons
	MenuManager(int reserveSize); //runs Buttons.reserve(reserveSize) instead

	//to be implemented when Message struct created
	//bool ReceiveMessage(Message theMessage); //adds message to the MessageQueue

	//to be implemented when Message struct created
	//bool ReadMessage(Message redMessage); //reads the latest message in the MessageQueue, and removes it.
	//									//if there are no messages, returns false.

	void DecodeMessage(int messageValue); //reads the passed-in message value, acts on it
										//0 for "mouse moved"
										//1 for "left mouse pressed in"
										//2 for "left mouse released"
										//3 for "ENTER pressed"
										//4 for "Up key pressed"
										//5 for "Down key pressed"

	//creates a MenuButton object, stores it in the Buttons vector array and returns true on success
	//needs Sprite support and Message struct
	//bool AddButton(Sprite buttonSprite, Sprite hoverSprite, Sprite pressedSprite,
	//	int width, int height, int posX, int posY, Message buttonMessage);

	void Update(); //to be run every frame. Changes selection based on mouse/keyboard inputs,
				//modifies MenuButtons in the Buttons vector array based on selection,
				//and tells a MenuButton to send its message if it is clicked on/ENTER'd.
				//also tells MenuButtons to be drawn.
};