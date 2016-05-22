//created 5/21/2016 at 1:32 AM EST by Derek Baumgartner
//MenuManager class, for managing menus!
//updated 5/22/2016 at 5:39 AM EST by Derek Baumgartner
//to add support for GSPMessage system and have the class contain a pointer to 
//the controlling InputManager

#pragma once
#include <vector>
#include "MenuButton.h"

//declare the InputManager class here, for usage in this class
class InputManager;

class MenuManager
{
private:

	//default constructor. Should not be used! privatized to discourage its use
	MenuManager();

	std::vector<MenuButton> Buttons; //vector array for storing this menu's buttons

	std::vector<GSPMessage> MessageQueue; //vector array for storing messages sent to this Menu

	int currentSelection; //currently selected button in the vector array

	InputManager* myManager; //the InputManager this menu is dependent upon

	//selection incrementation/decrementation functions.
	//these should not run if the mouse moved in the current frame,
	//OR if Buttons.size() <= 1.
	void DecrementSelection();
	void IncrementSelection();

public:

	friend class MenuButton; //allows this class to modify private MenuButton values and call its privatized constructor

	//constructor. sets currentSelection to 0, Buttons.reserve(reserveSize), and sets
	//myManger to the passed-in inputmanager
	MenuManager(InputManager inputmanager, int reserveSize);

	bool ReceiveMessage(GSPMessage theMessage); //adds message to the MessageQueue

	bool ReadMessage(GSPMessage &redMessage); //reads the latest message in the MessageQueue, and removes it.
										//if there are no messages, returns false.

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