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

#include "GSPWindow.h"
#include "Graphics.h"
#include "Text.h"
#include "Font.h"
#include "InputManager.h"
#include "Sprite.h"
#include "MessageHandler.h"
#include "MenuManager.h"
#include "Stella_temp.h"
#include "Plane.h"
#include "DepthBatch.h"

//main function - throws error if window fails
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
  GSPWindow gameWindow(L"Testing Window", 1080, 600);
  Graphics gfx(gameWindow);
  InputManager input(gameWindow);
  DepthBatch batch;

  MenuManager *testMenu = new MenuManager(input);

  Font font(L"Arial");
  font.setColor(D2D1::ColorF(0,1));
  font.setSize(40.0f);

  Text text(L"Example of Text!", &font);
  text.setRect(GSPRect(200.f, 300.f, 200.f, 200.f));
  batch.addRO(&text);
  text.z = 0;

  Stella stella;
  batch.addRO(&stella);
  stella.z = 100;

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
  coinSprites[0].destRect.x = 10;
  coinSprites[0].destRect.y = 200;

  //copy the sprite into the other coin sprites,
  //but change srcRect so they use a diff part of the tex
  for (int i = 1; i < 7; i++)
  {
	  coinSprites[i] = coinSprites[0];
	  coinSprites[i].srcRect.x += (coinSprites[i].srcRect.width)*i;
  }

  //create the first example button - no message
  testMenu->AddButton(coinSprites[0], coinSprites[5], coinSprites[6],
	  coinSprites[0].srcRect.width, coinSprites[0].srcRect.height, coinSprites[0].destRect.x, coinSprites[0].destRect.y, GSPMessage(RNONE, 0));

  //scoot the destRect.x over by 100, then create a new button
  for (int i = 0; i < 7; i++)
	  coinSprites[i].destRect.x += 100;

  //create the second example button - no message
  testMenu->AddButton(coinSprites[0], coinSprites[5], coinSprites[7],
	  coinSprites[0].srcRect.width, coinSprites[0].srcRect.height, coinSprites[0].destRect.x, coinSprites[0].destRect.y, GSPMessage(RNONE, 0));

  //scoot the destRect.x over by another 100, then create a new button
  for (int i = 0; i < 7; i++)
	  coinSprites[i].destRect.x += 100;

  //create the third example button - no message
  testMenu->AddButton(coinSprites[0], coinSprites[5], coinSprites[1],
	  coinSprites[0].srcRect.width, coinSprites[0].srcRect.height, coinSprites[0].destRect.x, coinSprites[0].destRect.y, GSPMessage(RNONE, 0));

  batch.addRO(testMenu);

  while(gameWindow.update()) {
	  input.ReadFrame();
	  if(input.IsKeyPressed(InputManager::KEY_ESC)) { break; }

      if(input.IsKeyPressed(InputManager::KEY_DASH)) { stella.update(); }

	  //replacement code for updating menu, that does not use messaging system. to be updated when messaging system
	  //fully online
	  if (input.MouseMoved()) { testMenu->ReceiveMessage(new GSPMessage(RTESTMENU, 0)); }
	  if (input.IsMouseTriggered(InputManager::MOUSE_LEFT)) { testMenu->ReceiveMessage(new GSPMessage(RTESTMENU, 1)); }
	  if (input.IsMouseReleased(InputManager::MOUSE_LEFT)) { testMenu->ReceiveMessage(new GSPMessage(RTESTMENU, 2)); }
	  if (input.IsKeyPressed(InputManager::KEY_ENTER)) { testMenu->ReceiveMessage(new GSPMessage(RTESTMENU, 3)); }
	  if (input.IsKeyPressed(InputManager::KEY_UP) || input.IsKeyPressed(InputManager::KEY_W)) {
		  testMenu->ReceiveMessage(new GSPMessage(RTESTMENU, 4));
	  }
	  if (input.IsKeyPressed(InputManager::KEY_DOWN) || input.IsKeyPressed(InputManager::KEY_S)) {
		  testMenu->ReceiveMessage(new GSPMessage(RTESTMENU, 5));
	  }

	  testMenu->Update();

      plane.scrollx += 2;

	  gfx.startDraw();
      batch.draw();
      gfx.endDraw();
  }

	return 0;
}

