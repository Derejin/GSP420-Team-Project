//created 5/21/2016 at 1:40 AM EST by Derek Baumgartner
//MenuButton class, for use by MenuManager in menu creation!
//updated 5/22/2016, at 5:34 AM EST by Derek Baumgartner
//to add GSPMessage structure to be utilized for sending messages, and to implement
//the GiveMessage method (GiveMessage to be completed in Wk4, with addition of a Message system).
//updated 5/23/2016, to add in the sprite support and move around messaging information

//to mark this as a file that may need changing if the messaging system is changed,
//here's the menu change symbol: ~~~m

#pragma once
#include "Sprite.h"
#include "GSPMessage.h"

class MenuButton
{
	//so MenuManager can access the constructor!
	friend class MenuManager;

private:
	//default constructor - also made private. should not be used!
	MenuButton();

	Sprite buttonSprites[3]; //array for sprites to be used for the button.
							//buttonSprites[0] is default, [1] is when it's selected/hovered over,
							//[2] is when the left mouse button is clicked on it

	int currentSprite; //current button sprite - which sprite is displayed

	int spriteWidth; //width of the button, for detecting if mouse is hovering over
					 //this button

	int spriteHeight; //height of this button, for detecting if mouse is hovering
					  //over this button

	int posX; //where to draw the button - also for detecting mouse
	int posY; //where to draw the button - also for detecting mouse

	GSPMessage buttonMessage; //message to be sent when button is clicked or selected+ENTER'd.
						   //Message struct contains message recipient and the message itself

protected:
	//constructor, protected so it can only be called by MenuManager
	//builds according to arguments
	MenuButton(Sprite buttonSprite, Sprite hoverSprite, Sprite pressedSprite,
		int width, int height, int X, int Y, GSPMessage theMessage);

public:

	bool IsHover(int X, int Y); 	//checks X coordinate against posX and spriteWidth
									//checks Y coordinate against posY and spriteHeight
									//returns true if both fall within/on the related values

	//may be modified depending on what Message struct we use
	GSPMessage ReturnMessage(); //sends the "buttonMessage" Message to its recipients

	int GetSprite() { return currentSprite; } //getter for currentSprite!

	void UpdateSprite(int spriteState); 	//updates currentSprite to the corresponding argument int value
											//0 means regular. updates (not hovered over)
											//1 means hoverSprite (mouse over button, but not pressed in)
											//2 means pressedSprite (mouse over button when left mouse pressed)

	void Draw(); //draws the sprite! needs Sprite support to draw, however.
};