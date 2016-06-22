#pragma once
#include "BaseRecipient.h"

//despite the name, this class ended up being used in all scenes
//it serves as a recipient for messages sent by the menu system
//and retains the value of the last recieved message as a public member

class TitleSceneMessageBox : public BaseRecipient
{
public:
	void DecodeMessage(int messageValue);

	int acceptedValue = 0;
};