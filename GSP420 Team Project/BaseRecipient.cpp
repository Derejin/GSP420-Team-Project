//created 5/23/2016 at 3:43 AM EST, 
//to define methods for the BaseRecipient class!

//to mark this as a file that may need changing if the messaging system is changed,
//here's the menu change symbol: ~~~m

#include "BaseRecipient.h"

//default constructor - just runs MessageQueue.reserve(4).
BaseRecipient::BaseRecipient() {
	MessageQueue.reserve(4);
}

//ReceiveMessage, for adding the message to MessageQueue!
bool BaseRecipient::ReceiveMessage(GSPMessage *theMessage)
{
	MessageQueue.push_back(theMessage);

	return true;
}

//if there's a message in the MessageQueue, pass it into the argument message value
//then remove the message from the queue
//return true if there's a message
bool BaseRecipient::ReadMessage(GSPMessage *redMessage)
{
	//if there are messages
	if (MessageQueue.size() > 0)
	{
		//copy latest message value
		redMessage = MessageQueue.front();

		//remove it from the queue
		MessageQueue.erase(MessageQueue.begin());

		//then return true
		return true;
	}
	//otherwise, return false
	else
		return false;
}