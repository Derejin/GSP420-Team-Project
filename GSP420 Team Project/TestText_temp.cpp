#include "TestText_temp.h"


TestText::TestText() : font(L"Ariel"), text(L"Press W or S to select a button, and press ENTER to use it!", &font){
	text.setRect(GSPRect(400.f, 150.f, 200.f, 200.f));
	font.setColor(D2D1::ColorF(0, 1));
	text.setFont(&font);
}

void TestText::DecodeMessage(int messageValue)
{
	switch (messageValue)
	{
	case 0: //move up
		text.setRect(GSPRect(400.f, 100.f, 200.f, 200.f));
		text.setString(L"See? The text string moved!");

		break;

	case 1: //move down
		text.setRect(GSPRect(400.f, 500.f, 200.f, 200.f));
		text.setString(L"Text string moved over here!");

		break;

	case 2: //back into position
		text.setRect(GSPRect(400.f, 150.f, 200.f, 200.f));
		text.setString(L"Pressing that button just moves the text back to here!");

	default:
		//nothing
		break;
	}
}

void TestText::Update(){
	//currentMessage, for storing and acting upon the received messages if there are any
	GSPMessage* currentMessage = nullptr;

	//read latest message, if there is one. decode it, delete it, then read the next and decode it.
	while (ReadMessage(currentMessage))
	{
		//decode
		DecodeMessage(currentMessage->theMessage);
		//delete
		delete currentMessage;
	}
}

void TestText::draw() {
	text.draw();
}

