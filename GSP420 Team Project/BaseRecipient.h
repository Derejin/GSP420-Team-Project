//created 5/23/2016 at 3:38 AM EST by Derek Baumgartner
//to act as a basis for classes that need to receive messages!

//to mark this as a file that may need changing if the messaging system is changed,
//here's the menu change symbol: ~~~m

#pragma once

#include <vector>
#include "GSPMessage.h"

//BaseRecipient class!
//contains a queue for storing GSPMessages, as well as a function for
//receiving messages and a virtual function for decoding them
class BaseRecipient
{
private:
	//queue for storing messages
	std::vector<GSPMessage*> MessageQueue;

public:	
	//function for storing a message in the MessageQueue
	bool ReceiveMessage(GSPMessage* theMessage);

	//function for checking if there is a message in the queue;
	//if there is, that message is copied into the passed in "theMessage" argument
	//then said message removed from MessageQueue and "true" is returned
	bool ReadMessage(GSPMessage *&theMessage);

	//virtual function for decoding the message. To be defined by any inheritors.
	//after passing in the messagevalue, be sure you delete the message!
	virtual void DecodeMessage(int messageValue) {}

  //decode all waiting messages (and empty the queue)
  void processQueue();
};