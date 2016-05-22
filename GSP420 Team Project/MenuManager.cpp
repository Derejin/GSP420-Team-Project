//created 5/21/2016 at 1:57 AM EST by Derek Baumgartner
//MenuManager method definitions!
//updated 5/22/2016 at 5:40 AM EST by Derek Baumgartner
//to add GSPMessage support and point to the passed-in InputManager

#include "MenuManager.h"
#include "InputManager.h"

//parameterized constructor!
MenuManager::MenuManager(InputManager inputmanager, int reserveSize)
{
	//initialize currentSelection
	currentSelection = 0;

	//set pointer towards the passed-in InputManager
	myManager = &inputmanager;

	//and reserve the requested amount of spots in Buttons!
	Buttons.reserve(reserveSize);
}


//ReceiveMessage, for adding the message to MessageQueue!
bool MenuManager::ReceiveMessage(GSPMessage theMessage)
{
	MessageQueue.push_back(theMessage);

	//for success
	return true;
}


//if there's a message in the MessageQueue, read the latest message
//and store it in the passed-in Message argument
bool MenuManager::ReadMessage(GSPMessage &redMessage)
{
	//if there are messages
	if (MessageQueue.size() > 0)
	{
		//copy latest message value
		GSPMessage redMessage = MessageQueue.front();

		//and remove it
		MessageQueue.erase(MessageQueue.begin());

		//then return true
		return true;
	}
	//otherwise, return false
	else
		return false;
}

//reads the passed in messageValue, performs the action.
//only call this during Update.
void MenuManager::DecodeMessage(int messageValue)
{
	//for preventing key usage if any message in the current read is Mouse Moved (i.e. 0)
	bool MouseHasntMoved = true;

	//current mouse position, red from the controlling InputManager
	Point MousePosition = myManager->GetMouseLocation();

	switch (messageValue)
	{
	case 0: //mouse moved

		//since mouse moved, set MouseHasntMoved to false
		MouseHasntMoved = false;

		//and for each button
		for (int i = 0; i < Buttons.size() - 1; i++)
		{
			//check if the mouse is hovering over it
			if (Buttons[i].IsHover(MousePosition.X, MousePosition.Y))
			{
				//deselect current Button
				Buttons[currentSelection].UpdateSprite(0);
				//update currentSelection
				currentSelection = i;
				//and that selected button's sprite
				Buttons[currentSelection].UpdateSprite(1);

				//then set i to Buttons.size() to end the loop
				i = Buttons.size();
			}
		}
		break;

	case 1: //left mouse button pressed in

		//check if the mouse is hovering over the current button
		if (Buttons[currentSelection].IsHover(MousePosition.X, MousePosition.Y))
		{
			//tell that button to jump to Sprite 2, if so.
			Buttons[currentSelection].UpdateSprite(2);
		}

		break;

	case 2: //left mouse button released after being pressed in previously

		//check if the mouse is currently over this button, and if its
		//sprite is Sprite 2
		if (Buttons[currentSelection].IsHover(MousePosition.X, MousePosition.Y)
			&& Buttons[currentSelection].GetSprite() == 2)
		{
			//tell this button to send its message, and go back to Sprite 1.
			Buttons[currentSelection].GiveMessage();
			Buttons[currentSelection].UpdateSprite(1);
		}
		//if not, just set the button to Sprite 0.
		else
			Buttons[currentSelection].UpdateSprite(0);

		break;

	case 3: //ENTER pressed

		//just tell current button to send its message!
		Buttons[currentSelection].GiveMessage();

		break;

	case 4: //Up key pressed

		//if the mouse hasn't moved this frame and if there's more than one button,
		//decrement selection
		if (MouseHasntMoved && Buttons.size() > 1)
			DecrementSelection();

		break;

	case 5: //Down key pressed

		//if the mouse hasn't moved this frame and if there's more than one button,
		//increment selection
		if (MouseHasntMoved && Buttons.size() > 1)
			IncrementSelection();

		break;

	default:
		//do nothing
		break;
	}
}

//to be implemented when Sprite support added for MenuButton
/*
//AddButton! Creates a button, adds it to the Buttons vector array
bool MenuManager::AddButton(Sprite buttonSprite, Sprite hoverSprite, Sprite pressedSprite,
	int width, int height, int posX, int posY, Message buttonMessage)
{
	Buttons.push_back(MenuButton(buttonSprite, hoverSprite, 
		pressedSprite, width, height, posX, posY, buttonMessage));
}*/

//DecrementSelection! Decrements currentSelection and alters the Buttons
//vector array accordingly
//do not call if mouse moved this frame, or if Buttons.size() <= 1
void MenuManager::DecrementSelection()
{
	//de-select current button by setting its sprite to 0
	Buttons[currentSelection].UpdateSprite(0);

	//if currentSelection > 0, then decrement it
	if (currentSelection > 0)
		currentSelection--;
	//otherwise, set it to the last button in Buttons
	else
		currentSelection = (Buttons.size() - 1);

	//then update the currently-selected button's sprite
	Buttons[currentSelection].UpdateSprite(1);
}

//IncrementSelection! Increments currentSelection and alters the Buttons
//vector array accordingly
//do not call if mouse moved this frame, or if Buttons.size() <= 1
void MenuManager::IncrementSelection()
{
	//de-select current button by setting its sprite to 0
	Buttons[currentSelection].UpdateSprite(0);

	//if currentSelection is not the last button in the Buttons vector array,
	//then increment it
	if (currentSelection < Buttons.size() - 1)
		currentSelection++;
	//otherwise, set it to the first button
	else
		currentSelection = 0;

	//then update the currently-selected button's sprite
	Buttons[currentSelection].UpdateSprite(1);
}


//Update function! Should be run every frame.
//changes selection based on received mouse/keyboard input messages,
//and modifies the MenuButtons in Buttons accordingly. Also responsible
//for drawing the buttons and telling a button to send its message if
//it is ENTER'd/clicked.
void MenuManager::Update()
{
	//message reading logic likely needs updating!

	//currentMessage, for storing the message Update currently is acting upon
	//set its message to 401, for "no message found"
	GSPMessage currentMessage(401);

	//read latest message, if there is one. decode it, then read the next and decode it.
	while(ReadMessage(currentMessage))
		DecodeMessage(currentMessage.theMessage);

	//draw all the buttons in the Buttons array
	for (int i = 0; i < Buttons.size() - 1; i++)
		Buttons[i].Draw();
}