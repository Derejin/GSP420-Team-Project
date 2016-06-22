#pragma once
#include "Sprite.h"
#include "Utility.h"
#include "RenderObject.h"

//The Plane class implements a fullscreen RenderObject.
//In order to use it, create an instance and call the setTexture()
//to bind a texture to draw from.
//Usage is generally similar to Sprite, but Plane is fullscreen and
//can be used for continually scrolling backgrounds or foregrounds
//that repeat at their borders.

class Plane : public RenderObject {
public:
  void setTexture(Texture& texture);
  void draw();

	float opacity = 1.0f;
	GSPRect srcRect;
  float scrollx = 0;
  float scrolly = 0;

private:
	Sprite sprites[4];

	friend class Graphics;
  static GSPRect screenRect; //set in bootstrap

};
