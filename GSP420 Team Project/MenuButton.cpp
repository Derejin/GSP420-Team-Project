//created 5/21/2016 at 1:47 AM EST by Derek Baumgartner
//MenuButton method definitions! will require Sprite support and a Message struct to be completed
//updated 5/22/2016 at 5:51 AM EST by Derek Baumgartner,
//to add the GiveMessage function - to be completed in Wk4.
//updated 5/23/2016 at 3:10 AM EST by Derek Baumgartner
//to add Sprite information now that there's sprite support!
//edited 5/26/2016 at 11:36 AM EST by Derek
//to update to GSPRect and attempt fixing an issue with buttons failing to draw properly

//to mark this as a file that may need changing if the messaging system is changed,
//here's the menu change symbol: ~_~m

#include "MenuButton.h"

//constructor! simply sets the values to the passed-in arguments.
//do not use default constructor! default constructor is privatized to prevent doing so.
MenuButton::MenuButton(Sprite buttonSprite, Sprite hoverSprite, Sprite pressedSprite,
	GSPRect Rect, GSPMessage theMessage) {

	buttonSprites[0] = buttonSprite;
	buttonSprites[1] = hoverSprite;
	buttonSprites[2] = pressedSprite;

	buttonRect = Rect;
	buttonMessage = theMessage;
	currentSprite = SPRITE_REGULAR;
}

//ReturnMessage! To return the message stored in this button.
GSPMessage MenuButton::ReturnMessage()
{
	return buttonMessage;
}

//IsHover - returns true if the passed in values are within the button
bool MenuButton::IsHover(int X, int Y)
{
	//check X coord
	if (X >= buttonRect.x && X <= (buttonRect.x + buttonRect.width))
		//check Y coord
		if (Y >= buttonRect.y && Y <= (buttonRect.y + buttonRect.height))
			return true;

	//if either fails, return false
	return false;
}

//UpdateSprite, for updating the sprite!
void MenuButton::UpdateSprite(SpriteType spriteState)
{
	currentSprite = spriteState;
}

//Draw function, for drawing the current sprite during a Draw pass. To be called by the managing MenuManager.
void MenuButton::draw()
{
	buttonSprites[currentSprite].draw();
}