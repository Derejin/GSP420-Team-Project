//created 5/23/2016 at 3:25 AM EST by Derek Baumgartner
//to act as a basis for a simple Messaging system
//this messaging system may be replaced later if we need to integrate with the
//GSP420 project

//this file contains the GSPMessage struct and an enum list of potential recipients

//to mark this as a file that may need changing if the messaging system is changed,
//here's the menu change symbol: ~_~m

#pragma once

//enum RClass (recipient class) - contains list of recipients!
enum RClass
{
	RNONE, //no recipient
	RTESTMENU, //for test version of menumanager, for Wk4 Code Demonstration+Testing
	RSTELLA, //for code demonstration - stella object
	RSCENE //for the current scene's message box
};

//GSPMessage structure!
struct GSPMessage
{
	RClass Recipient; //desired recipient!

	int theMessage; //message value that will be performed

	//default constructor! just null values
	GSPMessage()
	{
		Recipient = RNONE;
		theMessage = 0;
	}

	//parameterized constructor!
	GSPMessage(RClass desiredRecipient, int DesiredMessage)
	{
		Recipient = desiredRecipient;
		theMessage = DesiredMessage;
	}
};