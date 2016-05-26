#pragma once
#include "Texture.h"
#include "Utility.h"
#include "RenderObject.h"

class Sprite : public RenderObject {
public:
	void setBitmap(Texture& texture);
	void draw();

	float opacity= 1.0f;
	GSPRect srcRect;
	GSPRect destRect;

private:
	CComPtr<ID2D1Bitmap> bmp;

	friend class Graphics;
  //set this in bootstrap
  static Graphics* gfx;

};
