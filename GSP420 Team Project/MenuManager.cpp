//created 5/21/2016 at 1:57 AM EST by Derek Baumgartner
//MenuManager method definitions!
//updated 5/22/2016 at 5:40 AM EST by Derek Baumgartner
//to add GSPMessage support and point to the passed-in InputManager
//updated 5/23/2016 at 3:16 AM EST by Derek Baumgartner
//to fill out some sections now that there's Sprite support 
//and update message-related goodies
//updated 5/24/2016 at 4:34 PM by Derek, with help from Richard,
//to fix constructor and various other goodies


//to mark this as a file that may need changing if the messaging system is changed,
//here's the menu change symbol: ~~~m

#include "MenuManager.h"
#include "InputManager.h"
#include "MessageHandler.h" //for access to the MessageHandler singleton.

//parameterized constructor!
MenuManager::MenuManager(InputManager &inputmanager)
{
	currentSelection = 0;

	//set pointer towards the passed-in InputManager
	myManager = &inputmanager;
}

//reads the passed in messageValue, performs the action.
//only call this during Update.
void MenuManager::DecodeMessage(int messageValue)
{
	//for preventing key usage if any message in the current read is Mouse Moved (i.e. 0)
	bool MouseHasMoved = false;

	//current mouse position, red from the controlling InputManager
	Point MousePosition = myManager->GetMouseLocation();

	switch (messageValue)
	{
	case 0: //mouse moved

		//since mouse moved, set MouseHasntMoved to false
		MouseHasMoved = true;

		//and for each button
		for (size_t i = 0; i < Buttons.size(); i++)
		{
			//check if the mouse is hovering over it
			if (Buttons[i].IsHover(MousePosition.X, MousePosition.Y))
			{
				//deselect current Button
				Buttons[currentSelection].UpdateSprite(MenuButton::SPRITE_REGULAR);
				//update currentSelection
				currentSelection = (int)i;
				//and that selected button's sprite
				Buttons[currentSelection].UpdateSprite(MenuButton::SPRITE_HOVER);

				break;
			}
		}
		break;

	case 1: //left mouse button pressed in

		//check if the mouse is hovering over the current button
		if (Buttons[currentSelection].IsHover(MousePosition.X, MousePosition.Y))
		{
			//tell that button to jump to Sprite Pressed, if so.
			Buttons[currentSelection].UpdateSprite(MenuButton::SPRITE_PRESSED);
		}

		break;

	case 2: //left mouse button released after being pressed in previously

		//check if the mouse is currently over this button, and if its
		//sprite is Sprite Pressed
		if (Buttons[currentSelection].IsHover(MousePosition.X, MousePosition.Y)
			&& Buttons[currentSelection].GetSprite() == MenuButton::SPRITE_PRESSED)
		{
			//just send the message!
			gMessageHandler->HandleMessage(new GSPMessage(Buttons[currentSelection].ReturnMessage()));

			//then set sprite back to hover
			Buttons[currentSelection].UpdateSprite(MenuButton::SPRITE_HOVER);
		}
		//if not, just set the button to Sprite Regular.
		else
			Buttons[currentSelection].UpdateSprite(MenuButton::SPRITE_REGULAR);

		break;

	case 3: //ENTER pressed

		//just send the message!
		gMessageHandler->HandleMessage(new GSPMessage(Buttons[currentSelection].ReturnMessage()));

		break;

	case 4: //Up key pressed

		//if the mouse hasn't moved this frame and if there's more than one button,
		//decrement selection
		if (!MouseHasMoved && Buttons.size() > 1)
			DecrementSelection();

		break;

	case 5: //Down key pressed

		//if the mouse hasn't moved this frame and if there's more than one button,
		//increment selection
		if (!MouseHasMoved && Buttons.size() > 1)
			IncrementSelection();

		break;

	default:
		//do nothing
		break;
	}
}


//AddButton! Creates a button, adds it to the Buttons vector array
void MenuManager::AddButton(Sprite buttonSprite, Sprite hoverSprite, Sprite pressedSprite,
	GSPRect Rect, GSPMessage buttonMessage)
{
	Buttons.emplace_back(MenuButton(buttonSprite, hoverSprite, 
		pressedSprite, Rect, buttonMessage));
}

//DecrementSelection! Decrements currentSelection and alters the Buttons
//vector array accordingly
//do not call if mouse moved this frame, or if Buttons.size() <= 1
void MenuManager::DecrementSelection()
{
	//de-select current button by setting its sprite to regular
	Buttons[currentSelection].UpdateSprite(MenuButton::SPRITE_REGULAR);

	//if currentSelection > 0, then decrement it
	if (currentSelection > 0)
		currentSelection--;
	//otherwise, set it to the last button in Buttons
	else
		currentSelection = (int)Buttons.size() - 1;

	//then update the currently-selected button's sprite
	Buttons[currentSelection].UpdateSprite(MenuButton::SPRITE_HOVER);
}

//IncrementSelection! Increments currentSelection and alters the Buttons
//vector array accordingly
//do not call if mouse moved this frame, or if Buttons.size() <= 1
void MenuManager::IncrementSelection()
{
	//de-select current button by setting its sprite to regular
	Buttons[currentSelection].UpdateSprite(MenuButton::SPRITE_REGULAR);

	//if currentSelection is not the last button in the Buttons vector array,
	//then increment it
	if ((size_t)currentSelection < Buttons.size() - 1)
		currentSelection++;
	//otherwise, set it to the first button
	else
		currentSelection = 0;

	//then update the currently-selected button's sprite
	Buttons[currentSelection].UpdateSprite(MenuButton::SPRITE_HOVER);
}


//Update function! Should be run every frame.
//changes selection based on received mouse/keyboard input messages,
//and modifies the MenuButtons in Buttons accordingly. Also responsible
//for drawing the buttons and telling a button to send its message if
//it is ENTER'd/clicked.
void MenuManager::Update()
{
	//message reading logic likely needs updating!

	//currentMessage, for storing and acting upon the received messages if there are any
	GSPMessage* currentMessage = nullptr;

	//read latest message, if there is one. decode it, delete it, then read the next and decode it.
	while (ReadMessage(currentMessage))
	{
		//decode
		DecodeMessage(currentMessage->theMessage);
		//delete
		delete currentMessage;
	}
}

void MenuManager::draw()
{
	//draw all the buttons in the Buttons array
	for (auto& btn : Buttons) { btn.draw(); }
}