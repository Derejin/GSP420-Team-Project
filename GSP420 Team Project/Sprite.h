#pragma once
#include "Texture.h"
#include "Utility.h"
#include "RenderObject.h"

//This is the primary object for displayign images onscreen.
//To use Sprite, create an instance, then use setBitmap() to
//bind a source texture. Please review the public member comments.

class Graphics;

class Sprite : public RenderObject {
public:
  //binds a source texture to draw from
	void setBitmap(Texture& texture);
  //draws to the screen based on the current state of the object
	void draw();

  //adjust the object's opacity as desired. Note that transparent
  //objects must be drawn after the objects behind them in order
  //to blend correctly.
	float opacity= 1.0f;
  
  //This rect describes what portion of the source texture to use
  //when drawing. For convenience, when setBitmap() is called 
  //this rect is set to (0, 0, textureWidth, textureHeight).
  //It can be adjusted from there to only render a portion of the
  //texture.
	GSPRect srcRect;

  //This rect describes where the sprite should appear on the screen.
  //The size is not required to match the source rect, so using a different
  //size can stretch the image if desired. By default this is set to (0,0,0,0)
  //so you'll want to be sure to change it if you want to see anything when
  //drawing the sprite.
	GSPRect destRect;

private:
	CComPtr<ID2D1Bitmap> bmp;

	friend class Graphics;
  static Graphics* gfx; //set in bootstrap

};
