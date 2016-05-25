//created 5/20, 14:37PST, by Richard
//This class is effectively the text/font version of a Sprite.
//It represents a set of render data that can be drawn during a draw pass.

#pragma once
#include <string>
#include <d2d1.h>
#include "Utility.h"

class Font;

class Text {
public:
  Text(const std::wstring& string, Font* font);

  //The pixel rect in which to draw the text
  //Default is the whole viewport
    //Width will cause wrapping, but height will not cause clipping
    //The top of the text will be at the top or bottom of the rect,
    //depending which is closer to the top of the screen.
    //Ideally this would be replaced with setPos() and setWrap(), but
    //those can be added later as extensions if needed.
  void setRect(GSPRect rect);

  //Swap out Font object
  void setFont(Font* font);

  //change the string to render
  void setString(const std::wstring& string);

  //can only be used during a draw pass
  void draw();

private:
  D2D1_RECT_F rect;
  std::wstring string;
  Font* font;

  friend class Font;

};
