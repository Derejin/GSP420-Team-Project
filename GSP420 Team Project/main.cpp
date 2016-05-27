//exists to test GSPWindow functionality.
//created 5/17/2016, 6:45 PM, by Derek Baumgartner 
//modified 5/17 16:42PST by Richard
//- removed exception handling clause and consolidated into main()
//- added test of update loop
//modified 5/17 17:16PST by Richard
//- added test of Graphics class
//modified 5/17 18:02PST by Richard
//- added Texture junk
//modified 5/20 14:24PST by Richard
//- changed file name to main.cpp, testing font functions
//modified 5/20 11:49EST by Derek
//-adding InputManager and InputManager testing - testing not working yet, key input not
//seemingly being read.
//modified 5/21 0:19EST by Derek
//-testing of input was working, but rectangle wasn't being set properly to 
//see the changes caused by pressing Z.
//modified 5/23 4:32EST by Derek
//to add tests for MenuManager, MenuButton, and the Messaging System
// however, bug encountered when attempting to instantiate MenuManager. Pushing as separate branch
// to see help from Richard.
//edited 5/26/2016 at 11:33 AM EST by Derek
//to update MenuButton+MenuManager to GSPRect and attempt fixing an issue with buttons failing to draw properly

#include "GSPWindow.h"
#include "Graphics.h"
#include "Text.h"
#include "Font.h"
#include "InputManager.h"
#include "Sprite.h"
#include "MessageHandler.h"
#include "MenuManager.h"
#include "Plane.h"
#include "DepthBatch.h"

//test files
#include "Stella_temp.h"
#include "TestText_temp.h"

//main function - throws error if window fails
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
  GSPWindow gameWindow(L"Testing Window", 1080, 600);
  Graphics gfx(gameWindow);
  InputManager input(gameWindow);
  DepthBatch batch;

  MenuManager *testMenu = new MenuManager(input);

  //messenger setup
  gMessageHandler->Instantiate();
  gMessageHandler->AddRecipient(testMenu, RTESTMENU);

  Font font(L"Arial");
  font.setColor(D2D1::ColorF(0,1));
  font.setSize(40.0f);

  Text text(L"Example of Text!", &font);
  text.setRect(GSPRect(200.f, 150.f, 200.f, 200.f));
  batch.addRO(&text);
  text.z = 0;

  Stella stella;
  batch.addRO(&stella);
  stella.z = 100;

  TestText * movableText = new TestText();
  gMessageHandler->AddRecipient(movableText, RTESTTEXT);
  batch.addRO(movableText);

  Texture bgtex(L"tilesetOpenGameBackground_3.png");

  Plane plane;
  plane.setTexture(bgtex);
  batch.addRO(&plane);
  plane.z = -100;

  //menu setup//
  Texture coinTex(L"Full Coins.png");
  Sprite coinSprites[8];

  coinSprites[0].setBitmap(coinTex);
  coinSprites[0].srcRect.width /= 8;

  coinSprites[0].destRect = coinSprites[1].srcRect;
  coinSprites[0].destRect.x = 540;
  coinSprites[0].destRect.y = 200;
  coinSprites[0].destRect.width = coinSprites[0].srcRect.width*2;
  coinSprites[0].destRect.height = coinSprites[0].srcRect.height*2;

  //copy the sprite into the other coin sprites,
  //but change srcRect so they use a diff part of the tex
  for (int i = 1; i < 7; i++)
  {
	  coinSprites[i] = coinSprites[0];
	  coinSprites[i].srcRect.x += (coinSprites[i].srcRect.width)*i;
  }

  //create GSPRect for the first button
  GSPRect firstButtonRect(coinSprites[0].destRect.x, coinSprites[0].destRect.y, 
	  coinSprites[0].destRect.width, coinSprites[0].destRect.height);

  //create the first example button, which tells testText to move up
  testMenu->AddButton(coinSprites[0], coinSprites[5], coinSprites[6],
	  firstButtonRect, GSPMessage(RTESTTEXT, 0));

  //scoot the destRect.x over by 100 for each sprite
  for (int i = 0; i < 7; i++)
	  coinSprites[i].destRect.x += 100;

  //set the GSPRect for the second button
  GSPRect secondButtonRect = firstButtonRect;
  secondButtonRect.x += 100;

  //create the second example button -  tells testText to move down
  testMenu->AddButton(coinSprites[0], coinSprites[5], coinSprites[6],
	  secondButtonRect, GSPMessage(RTESTTEXT, 1));

  //scoot the destRect.x over by another 100, then create a new button
  for (int i = 0; i < 7; i++)
	  coinSprites[i].destRect.x += 100;

  //set the GSPRect for the third button
  GSPRect thirdButtonRect = secondButtonRect;
  thirdButtonRect.x += 100;

  //create the third example button - tells testText to move back into starting position
  testMenu->AddButton(coinSprites[0], coinSprites[5], coinSprites[6],
	  thirdButtonRect, GSPMessage(RTESTTEXT, 2));

  batch.addRO(testMenu);

  while(gameWindow.update()) {
	  input.ReadFrame();
	  if(input.IsKeyPressed(InputManager::KEY_ESC)) { break; }

      if(input.IsKeyPressed(InputManager::KEY_DASH)) { stella.update(); }

	  //for testing if messaging system works
	 // if (input.IsKeyTriggered(InputManager::KEY_W)) { gMessageHandler->HandleMessage(new GSPMessage(RTESTTEXT, 0)); }
	 // if (input.IsKeyTriggered(InputManager::KEY_S)) { gMessageHandler->HandleMessage(new GSPMessage(RTESTTEXT, 1)); }
	 // if (input.IsKeyTriggered(InputManager::KEY_ENTER)) { gMessageHandler->HandleMessage(new GSPMessage(RTESTTEXT, 2)); }

	  if (input.MouseMoved()) { gMessageHandler->HandleMessage(new GSPMessage(RTESTMENU, 0)); }
	  if (input.IsMouseTriggered(InputManager::MOUSE_LEFT)) { gMessageHandler->HandleMessage(new GSPMessage(RTESTMENU, 1)); }
	  if (input.IsMouseReleased(InputManager::MOUSE_LEFT)) { gMessageHandler->HandleMessage(new GSPMessage(RTESTMENU, 2)); }
	  if (input.IsKeyTriggered(InputManager::KEY_ENTER)) { 
		  gMessageHandler->HandleMessage(new GSPMessage(RTESTMENU, 3));
		  //gMessageHandler->HandleMessage(new GSPMessage(RTESTTEXT, 2));
	  }
	  if (input.IsKeyTriggered(InputManager::KEY_UP) || input.IsKeyTriggered(InputManager::KEY_W)) {
		  gMessageHandler->HandleMessage(new GSPMessage(RTESTMENU, 4));
		  //gMessageHandler->HandleMessage(new GSPMessage(RTESTTEXT, 0));
	  }
	  if (input.IsKeyTriggered(InputManager::KEY_DOWN) || input.IsKeyTriggered(InputManager::KEY_S)) {
		  gMessageHandler->HandleMessage(new GSPMessage(RTESTMENU, 5));
		  //gMessageHandler->HandleMessage(new GSPMessage(RTESTTEXT, 1));
	  }
	  //menu must update first
	  testMenu->Update();

	  movableText->Update();

      plane.scrollx += 2;

	  gfx.startDraw();
      batch.draw();
      gfx.endDraw();
  }

	return 0;
}

