//created 5/23/2016 at 3:59 AM EST by Derek Baumgartner,
//to define methods for the MessageHandler!
//based on the GSP420 project "CoreManager" class.

//to mark this as a file that may need changing if the messaging system is changed,
//here's the menu change symbol: ~~~m

#include "MessageHandler.h"

//initialize global pointer
MessageHandler* gMessageHandler = 0;

//Instantiate function, for instantiating the only instance of this class
//and storing it in the globally-accessible pointer
void MessageHandler::Instantiate()
{
	static MessageHandler instance;
	gMessageHandler = &instance;
}

//AddRecipient! Takes a pointer to an object and ties it to 
//the passed-in enum RClass value.
void MessageHandler::AddRecipient(BaseRecipient* desiredRecipient, RClass recipientID)
{
	//If the vector memory has been allocated the replace the pointer
	if ((size_t)recipientID < RecipientList.size())
	{
		/* commenting out the delete functionality, since we store our MenuManagers by value
		if (RecipientList[(int)recipientID])
		{
			delete RecipientList[(int)recipientID];
		}*/
		RecipientList[(int)recipientID] = desiredRecipient;
	}
	//Or allocate the vector and add in the pointer, fill gap with 0.
	else
	{
		size_t oldsize = RecipientList.size();
		RecipientList.resize((int)recipientID + 1);
		for (size_t i = oldsize; i < RecipientList.size() - 1; ++i)
		{
			RecipientList[i] = 0;
		}
		RecipientList[(int)recipientID] = desiredRecipient;
	}
}

//RemoveRecipient, for removing the object tied to a particular ID.
//automatically handled by AddRecipient, so no need to call this
//if you want to replace the current object tied to an ID by another.
//only use this if you want to free up an ID without tying something else to it.
void MessageHandler::RemoveRecipient(RClass recipientID)
{
	if (RecipientList.size() - 1 > (size_t)recipientID)
	{
		//delete RecipientList[(int)recipientID];
		//commenting out the delete functionality, since we store our MenuManagers by value
		RecipientList[(int)recipientID] = 0;
	}
}

//send the passed-in message to its recipient!
bool MessageHandler::HandleMessage(GSPMessage *theMessage)
{
	//if the recipient is RNONE, then just end and return true.
	//shouldn't really occur, but here just in case.
	if (theMessage->Recipient == RNONE)
	{
		delete theMessage;
		return true;
	}
	else
	{
		//Pass the message to receiver, check if valid
		if (RecipientList.size() > (size_t)theMessage->Recipient && RecipientList[theMessage->Recipient])
		{
			if (RecipientList[theMessage->Recipient]->ReceiveMessage(theMessage))
			{
				return true;
			}
			else
			{
				if (theMessage)
				{
					delete theMessage;
				}
				return false;
			}
		}
		else
		{
			delete theMessage;
			return false;
		}
	}
}