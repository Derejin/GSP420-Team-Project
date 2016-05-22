//created 5/21/2016 at 1:47 AM EST by Derek Baumgartner
//MenuButton method definitions! will require Sprite support and a Message struct to be completed
//updated 5/22/2016 at 5:51 AM EST by Derek Baumgartner,
//to add the GiveMessage function - to be completed in Wk4.

#include "MenuButton.h"

//Constructor - needs Sprite and Message support to function
/*
MenuButton::MenuButton(Sprite buttonSprite, Sprite hoverSprite, Sprite pressedSprite,
	int width, int height, int posX, int posY, GSPMessage theMessage) {

	buttonSprites[0] = buttonSprite;
	buttonSprites[1] = hoverSprite;
	buttonSprites[2] = pressedSprite;

	spriteWidth = width;
	spriteHeight = height;

	this.posX = posX;
	this.posY = posY;
	buttonMessage = theMessage;
}*/

//GiveMessage! To send the message to its desired recipient.
//not named SendMessage due to a #definition for SendMessage already existing.
void MenuButton::GiveMessage()
{
	//currently no message receiver system in place, so it does nothing.
	//to be discussed wk4.
}



//IsHover - returns true if the passed in values are within the button
bool MenuButton::IsHover(int X, int Y)
{
	//check X coord
	if (X >= posX && X <= (posX + spriteWidth))
		//check Y coord
		if (Y >= posY && Y <= (posY + spriteHeight))
			return true;

	//if either fails, return false
	return false;
}

//UpdateSprite, for updating the sprite!
void MenuButton::UpdateSprite(int spriteState)
{
	currentSprite = spriteState;
}

//Draw function, for drawing the button during a Draw pass. To be called by the managing MenuManager.
void MenuButton::Draw()
{
	//will need Sprite support to draw!
}