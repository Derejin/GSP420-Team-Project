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

//Testing if this works
//Testing number two

#include "GSPWindow.h"
#include "Graphics.h"
#include "Text.h"
#include "Font.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Bitmap.h"

//set screen width and height here
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 600;

//main function - throws error if window fails
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
  GSPWindow gameWindow(L"Testing Window", SCREEN_WIDTH, SCREEN_HEIGHT);
  Graphics gfx(gameWindow);
  InputManager input(HINSTANCE(GetModuleHandle(NULL)), gameWindow.getHandle(), SCREEN_WIDTH, SCREEN_HEIGHT);

  //Bitmap objects serve as handles and information sources for loaded textures
  Bitmap stellaBmp = gfx.loadImageFromFile(L"stella_walk_2.png");

  Sprite stellaSpr = gfx.createSprite();
  stellaSpr.setBitmap(stellaBmp); //link this sprite to the loaded bitmap resource
	//these are setting the size of the source-rect that describes what portion of the texture to render (describes the size of an animation cell)
  stellaSpr.srcWidth = (float)(stellaBmp.getWidth() / 4);
  stellaSpr.srcHeight = (float)(stellaBmp.getHeight() / 8);
  //these are setting the size of the sprite itself (size to render at)
  stellaSpr.width = stellaSpr.srcWidth;
  stellaSpr.height = stellaSpr.srcHeight;
  //and the position to render at
  stellaSpr.x = (SCREEN_WIDTH - stellaSpr.width) / 2;
  stellaSpr.y = (SCREEN_HEIGHT - stellaSpr.height) / 2;

  Bitmap coinBmp = gfx.loadImageFromFile(L"Full Coins.png");
  std::vector<Sprite> sprites{ gfx.createSprite(), gfx.createSprite(), gfx.createSprite() };
  for (auto& spr : sprites) {
	  spr.setBitmap(coinBmp);//link this sprite to the loaded bitmap resource
		//these are setting the size of the source-rect that describes what portion of the texture to render (describes the size of an animation cell)
	  spr.srcWidth = (float)(coinBmp.getWidth() / 8);
	  spr.srcHeight = (float)coinBmp.getHeight();
	  //these are setting the size of the sprite itself (size to render at)
	  spr.width = spr.srcWidth * 2;
	  spr.height = spr.srcHeight * 2;
  }

  int tickCount = 0;  //render-locked timer

					  //Stella-specific animation stuff
  const int faceorder[] = { 0, 5, 1, 6, 3, 7, 2, 4 }; //spritesheet was in a weird order and I don't feel like changing it(from demo)
  int stepFreq = 10;   //how many ticks pass before advancing animation frame
  int turnFreq = 100; //how many ticks pass before changing direction
  int stepCells = 4;  //number of cells in walking loop (horizontal frames)
  int directions = 8; //number of directions represented (vertical frames)

					  //coin-specific animation stuff
  int coinFreq = 5; //how many ticks pass before advancing animation frame
  int coinFrames = 8; // how many different frames for this sprite
  float coinRot = 0;  // starting rotation
  float rotSpd = -0.01f; //speed of the rotation
  int rotRadius = 150; // radius of the rotation

  Font font(L"Arial");
  Text text(L"The herp derpinest.", &font);
  text.setRect(D2D1::RectF(100.f, 100.f, 300.f, 100.f));

  while(gameWindow.update()) {
	//to test input: will check for "Z" (KEY_DASH)
	//and change the text's rectangle
	  //currently not working.
	  input.ReadFrame();

	  if (input.IsKeyPressed(InputManager::KEY_DASH)) {
		  text.setRect(D2D1::RectF(200.f, 100.f, 400.f, 300.f));
	  }
	  else {
		  text.setRect(D2D1::RectF(100.f, 100.f, 300.f, 100.f));
	  }
	
	  tickCount++;

	  //update stella
	  stellaSpr.srcX = ((tickCount % (stepCells  * stepFreq)) / stepFreq) * stellaSpr.srcWidth;
	  stellaSpr.srcY = faceorder[((tickCount % (directions * turnFreq)) / turnFreq)] * stellaSpr.srcHeight;

	  //update coins
	  coinRot += rotSpd;
	  for (size_t i = 0; i < sprites.size(); i++) {
		  sprites[i].srcX = ((tickCount % (coinFrames * coinFreq)) / coinFreq) * sprites[0].srcWidth;
		  float myRot = coinRot + (i * 2.0944f); //offset angle by 1/3 of a rotation
		  sprites[i].x = (SCREEN_WIDTH / 2) + (rotRadius * cos(myRot));
		  sprites[i].y = (SCREEN_HEIGHT / 2) + (rotRadius * sin(myRot));
	  }
	gfx.startDraw();
	text.draw();
	
    gfx.endDraw();
  }

	return 0;
}

