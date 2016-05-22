
#pragma once
#include "Bitmap.h"
#include "Graphics.h"
#include <vector>

class Sprite {
	friend class Graphics;
public:
	Sprite(const Sprite& other);
	Sprite(Sprite&& other);
	~Sprite();
	void setBitmap(Bitmap& bitmap);
	float opacity;
	float x, y, width, height;
	float srcX, srcY, srcWidth, srcHeight;
	void draw(ID2D1HwndRenderTarget* renderTarget);
private:
	static Graphics* gfx;
	Sprite(Graphics& gfx);
	void listRegister();
	void listUnRegister();
	std::vector<Sprite*>& list;
	CComPtr<ID2D1Bitmap> bmp;
};