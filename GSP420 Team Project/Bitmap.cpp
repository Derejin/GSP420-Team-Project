#include "Bitmap.h"

Bitmap::Bitmap(ID2D1Bitmap* comBmp) : comObj(comBmp) {
	
}

unsigned Bitmap::getWidth() const {
	D2D1_SIZE_U dims = comObj->GetPixelSize();
	return dims.width;
}

unsigned Bitmap::getHeight() const {
	D2D1_SIZE_U dims = comObj->GetPixelSize();
	return dims.height;
}