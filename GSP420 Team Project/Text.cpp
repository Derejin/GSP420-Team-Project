//created 5/20, 14:37PST, by Richard

#include "Text.h"
#include "Font.h"
#include "Graphics.h"

Text::Text(const std::wstring& string, Font* font) : string(string), font(font) {
  auto vpsz = font->gfx->renderTarget->GetSize();
  rect = D2D1::RectF(0, 0, vpsz.width, vpsz.height);
}

void Text::setRect(GSPRect rect) {
  this->rect = rect;
}

void Text::setFont(Font* font) {
  this->font = font;
}

void Text::setString(const std::wstring& string) {
  this->string = string;
}

void Text::draw() {
  //the font object does not react to changes until resetFormat() is called (to prevent needless work)
  //any change will set the 'dirty' flag to true, so we check it here and reset the foramt only when needed
  if(font->dirty) { font->resetFormat(); }

  font->gfx->renderTarget->DrawText(string.c_str(), (UINT)string.size(), font->format, rect, font->brush);
}

