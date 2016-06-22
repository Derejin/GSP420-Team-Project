//created 5/20, 14:42PST, by Richard
//This class represents a loaded font face and formatting information,
//such as size/bold/italic/color
//a Font object can be linked to a Text object to enable it to draw text
//Multiple Text objects can safely share the same Font object

#pragma once
#include <string>
#include <d2d1.h>
#include <dwrite.h>
#include <atlbase.h>

class Graphics;
class Text;

class Font {
public:
  //Sizes are in points

  Font(const std::wstring& faceName, float size = 20.0f);

  void setSize(float size);
  void setBold(bool bold);
  void setItalic(bool italic);
  void setColor(D2D1::ColorF color); //default is white

private:
  void resetFormat();
  bool dirty = true;

  CComPtr<IDWriteTextFormat> format;
  CComPtr<ID2D1SolidColorBrush> brush;

  std::wstring faceName;
  float size;
  bool bold = false;
  bool italic = false;

  friend class Graphics;
  friend class Text;
  static Graphics* gfx; //set in bootstrap
  static CComPtr<IDWriteFactory> factory;

};
