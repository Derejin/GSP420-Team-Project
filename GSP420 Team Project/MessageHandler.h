//created 5/23/2016 at 3:52 AM EST by Derek Baumgartner
//to act as a hub in a simple message system!
//based on the GSP420 project "CoreManager" class.

//to mark this as a file that may need changing if the messaging system is changed,
//here's the menu change symbol: ~~~m

#pragma once
#include <vector>
#include "GSPMessage.h"
#include "BaseRecipient.h"

//MessageHandler! Contains list of potential recipients in a vector array,
//for sending messages via HandleMessage.
//This class is a Singleton!
class MessageHandler
{
private:
	//constructor, privatized so you can't create more!
	MessageHandler() {};

	//array of pointers to recipients
	std::vector<BaseRecipient*> RecipientList;

public:
	static void Instantiate(); //creates the singleton!

	//ties a recipient object to the RClass ID - kinda like tying a
	//P.O. box to a person.
	void AddRecipient(BaseRecipient* desiredRecipient, RClass recipientID);

	//frees up an RClass ID from the recipient tied to it.
	void RemoveRecipient(RClass recipientID);

	bool HandleMessage(GSPMessage *theMessage); //sends a message to the appropriate object!
};

//pointer for holding the singleton
extern MessageHandler* gMessageHandler;