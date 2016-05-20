//created 5/20, 14:37PST, by Richard

#include "Font.h"
#include "Graphics.h"
#pragma comment(lib, "dwrite.lib")
#include "Text.h"

//defining statics
Graphics* Font::gfx = nullptr; //this needs to be set during bootstrap
CComPtr<IDWriteFactory> Font::factory;

Font::Font(const std::wstring& faceName, float size) : faceName(faceName), size(size) {
  //init the static factory if it's not already present
  if(!factory.p) { DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&factory); }

  gfx->renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &brush);
}

//The dirty/clean strategy used to avoid needless thrashing of the format object.
//The Text::draw() function will check the dirty flag and reset the format object
//only when needed.

void Font::setSize(float size) {
  this->size = size;
  dirty = true;
}

void Font::setBold(bool bold) {
  this->bold = bold;
  dirty = true;
}

void Font::setItalic(bool italic) {
  this->italic = italic;
  dirty = true;
}

void Font::setColor(D2D1::ColorF color) {
  brush->SetColor(color);
}

void Font::resetFormat() {
  if(format.p) { format.Release(); }

  factory->CreateTextFormat(faceName.c_str(), NULL, 
    bold ? DWRITE_FONT_WEIGHT_BOLD : DWRITE_FONT_WEIGHT_REGULAR, 
    italic ? DWRITE_FONT_STYLE_ITALIC : DWRITE_FONT_STYLE_NORMAL, 
    DWRITE_FONT_STRETCH_NORMAL, size, L"en-us", &format);

  format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
  format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

  dirty = false;
}
