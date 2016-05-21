//created 5/21/2016 at 1:40 AM EST by Derek Baumgartner
//MenuButton class, for use by MenuManager in menu creation!

#pragma once
//#include Sprite.h - need Sprite support to work!

class MenuButton
{
private:
	//constructor, privatized so it can only be called by MenuManager, its friend class
	//builds menu button according to arguments. Needs Sprite support to work!
	//MenuButton(Sprite buttonSprite, Sprite hoverSprite, Sprite pressedSprite,
	//		int width, int height, int posX, int posY, Message theMessage);

	//default constructor - also made private. should not be used!
	MenuButton();

	//needs Sprite support to work!
	//Sprite buttonSprites[3]; //array for sprites to be used for the button.
							//buttonSprites[0] is default, [1] is when it's selected/hovered over,
							//[2] is when the left mouse button is clicked on it

	int currentSprite; //current button sprite - which sprite is displayed

	int spriteWidth; //width of the button, for detecting if mouse is hovering over
					 //this button

	int spriteHeight; //height of this button, for detecting if mouse is hovering
					  //over this button

	int posX; //where to draw the button - also for detecting mouse
	int posY; //where to draw the button - also for detecting mouse

	//needs Message struct to work!
	//Message buttonMessage; //message to be sent when button is clicked or selected+ENTER'd.
						   //Message struct contains message recipient and the message itself

public: //may make these private, since only MenuManager should be calling MenuButton and its methods

	bool IsHover(int X, int Y); 	//checks X coordinate against posX and spriteWidth
									//checks Y coordinate against posY and spriteHeight
									//returns true if both fall within/on the related values

	//may be modified depending on what Message struct we use
	bool SendMessage(); //sends the "buttonMessage" Message to its recipient, returns true on success

	int GetSprite() { return currentSprite; } //getter for currentSprite!

	void UpdateSprite(int spriteState); 	//updates currentSprite to the corresponding argument int value
											//0 means regular. updates (not hovered over)
											//1 means hoverSprite (mouse over button, but not pressed in)
											//2 means pressedSprite (mouse over button when left mouse pressed)

	void Draw(); //draws the sprite! needs Sprite support to draw, however.
};