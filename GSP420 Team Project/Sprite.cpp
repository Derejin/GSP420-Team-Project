#include "Sprite.h"
#include "Graphics.h"
#include <algorithm>

Sprite::Sprite(Graphics& gfx) : list(gfx.sprites) {
	listRegister();
}

Sprite::Sprite(const Sprite& other) :
	list(other.list),
	bmp(other.bmp),
	opacity(other.opacity),
	x(other.x),
	y(other.y),
	width(other.width),
	height(other.height),
	srcX(other.srcX),
	srcY(other.srcY),
	srcWidth(other.srcWidth),
	srcHeight(other.srcHeight)
{
	listRegister();
}

Sprite::Sprite(Sprite&& other) : Sprite(other) {
	other.listUnRegister();
	listRegister();
}

Sprite::~Sprite() {
	listUnRegister();
}

void Sprite::setBitmap(Bitmap& bitmap) {
	bmp = bitmap.comObj;
	opacity = 1.0f;
	width = (float)bitmap.getWidth();
	height = (float)bitmap.getHeight();
	srcX = 0;
	srcY = 0;
	srcWidth = width;
	srcHeight = height;
}

void Sprite::draw(ID2D1HwndRenderTarget* renderTarget) {
	D2D_RECT_F destRect = { x,    y,       x + width,       y + height };
	D2D_RECT_F srcRect = { srcX, srcY, srcX + srcWidth, srcY + srcHeight };
	renderTarget->DrawBitmap(bmp, destRect, opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, srcRect);
}

void Sprite::listRegister() {
	list.push_back(this);
}

void Sprite::listUnRegister() {
	auto iter = std::find(list.begin(), list.end(), this);
	if (iter == list.end()) { throw std::runtime_error("Attempted to unregister a Sprite that was not registered."); }
	list.erase(iter);
}