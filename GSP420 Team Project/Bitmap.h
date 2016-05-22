#pragma once
#pragma once
#include <d2d1.h>
#include <atlbase.h>

class Bitmap {
	friend class Graphics;
	friend class Sprite;
public:
	unsigned getWidth() const; //width for the bitmap 
	unsigned getHeight() const;//height for the bitmap
private:
	Bitmap(ID2D1Bitmap* comBmp);
	CComPtr<ID2D1Bitmap> comObj;// this is the Com bitmap object/may not be nessacery seems this is also in Texture
};