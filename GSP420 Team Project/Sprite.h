
#pragma once
#include "Texture.h"

class Sprite {
public:
	void setBitmap(Texture& texture);
	void draw();

	float opacity;
	D2D1_RECT_F srcRect;
	D2D1_RECT_F destRect;
	float srcWidth, srcHeight;
	

private:
	CComPtr<ID2D1Bitmap> bmp;

	friend class Graphics;
	static Graphics* gfx;

};