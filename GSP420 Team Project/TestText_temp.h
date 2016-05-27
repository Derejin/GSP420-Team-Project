//created to test messaging system by showing off text that moves when buttons are pressed!
//created 5/26/2016, 5:52 AM by Derek

#pragma once
#include "Text.h"
#include "Font.h"
#include "BaseRecipient.h"
#include "RenderObject.h"

class TestText : public BaseRecipient, public RenderObject
{
private:
	Font font;
	Text text;

public:
	TestText();

	void DecodeMessage(int messageValue);
	void Update();
	void draw();
};
