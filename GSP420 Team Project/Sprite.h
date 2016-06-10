#pragma once
#include "Texture.h"
#include "Utility.h"
#include "RenderObject.h"

class Graphics;

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
  static Graphics* gfx; //set in bootstrap

};
