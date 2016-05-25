//created by colton on 5/20
#include "Graphics.h"
#include "Plane.h"

Graphics* Plane::gfx = nullptr;
GSPRect Plane::destRect;

void Plane::setTexture(Texture& texture) {
	bmp = texture.comObj;
	srcRect = GSPRect(0, 0, (float)texture.getWidth(), (float)texture.getHeight());
}

void Plane::draw() {
  gfx->renderTarget->DrawBitmap(bmp, destRect, opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, srcRect);
}
