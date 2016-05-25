//created by colton on 5/20
#pragma once
#include "Texture.h"
#include "Utility.h"

class Plane {
public:
  void setTexture(Texture& texture);
  void draw();

	float opacity= 1.0f;
	GSPRect srcRect;
  int z = 0;

private:
	CComPtr<ID2D1Bitmap> bmp;

	friend class Graphics;
  //set these in bootstrap
	static Graphics* gfx;
  static GSPRect destRect;
};
