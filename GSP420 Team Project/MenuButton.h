//created 5/21/2016 at 1:40 AM EST by Derek Baumgartner
//MenuButton class, for use by MenuManager in menu creation!
//updated 5/22/2016, at 5:34 AM EST by Derek Baumgartner
//to add GSPMessage structure to be utilized for sending messages, and to implement
//the GiveMessage method (GiveMessage to be completed in Wk4, with addition of a Message system).

#pragma once
//#include Sprite.h - need Sprite support to work!

//GSPMessage structure!
//currently just contains an int value, but can be expanded/replaced with a new message
//structure for integration in Week 5, or after getting more information from the professor
struct GSPMessage
{
	int theMessage; //message value that will be performed
	//Datatype Recipient; //recipient! replace datatype when interactivity needed. likely will be enum.

	//parameterized constructor!
	GSPMessage(int DesiredMessage //, Datatype DesiredRecipient
									)
	{
		theMessage = DesiredMessage;
		//Recipient = DesiredRecipient;
	}
};

class MenuButton
{
private:
	//constructor, privatized so it can only be called by MenuManager, its friend class
	//builds menu button according to arguments. Needs Sprite support to work!
	//MenuButton(Sprite buttonSprite, Sprite hoverSprite, Sprite pressedSprite,
	//		int width, int height, int posX, int posY, GSPMessage theMessage);

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

	GSPMessage buttonMessage; //message to be sent when button is clicked or selected+ENTER'd.
						   //Message struct contains message recipient and the message itself

public: //may make these private, since only MenuManager should be calling MenuButton and its methods

	bool IsHover(int X, int Y); 	//checks X coordinate against posX and spriteWidth
									//checks Y coordinate against posY and spriteHeight
									//returns true if both fall within/on the related values

	//may be modified depending on what Message struct we use
	void GiveMessage(); //sends the "buttonMessage" Message to its recipients

	int GetSprite() { return currentSprite; } //getter for currentSprite!

	void UpdateSprite(int spriteState); 	//updates currentSprite to the corresponding argument int value
											//0 means regular. updates (not hovered over)
											//1 means hoverSprite (mouse over button, but not pressed in)
											//2 means pressedSprite (mouse over button when left mouse pressed)

	void Draw(); //draws the sprite! needs Sprite support to draw, however.
};