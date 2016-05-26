//created by colton on 5/20

#pragma once
#include "Sprite.h"
#include "Utility.h"
#include "RenderObject.h"

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
  //set this in bootstrap
  static GSPRect screenRect;
};
