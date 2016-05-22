#include "Sprite.h"
#include "Graphics.h"

Graphics* Sprite::gfx = nullptr;

void Sprite::setBitmap(Texture& texture) {
	bmp = texture.comObj;
	srcRect = D2D1::RectF(0, 0, texture.getWidth(), texture.getHeight());
}

void Sprite::draw() {
	gfx->renderTarget->DrawBitmap(bmp, destRect, opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, srcRect);
}

