#pragma once
#include "BaseRecipient.h"

class TitleSceneMessageBox : public BaseRecipient
{
public:
	void DecodeMessage(int messageValue);

	int acceptedValue = 0;
};