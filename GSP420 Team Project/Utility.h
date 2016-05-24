#pragma once
#include <d2d1.h>

struct GSPRect {
  float x = 0;
  float y = 0;
  float width = 0;
  float height = 0;

  GSPRect() {}

  GSPRect(float x, float y, float w, float h) : x(x), y(y), width(w), height(h) {}

  GSPRect(D2D1_RECT_F d2dRect) {
    x = d2dRect.left;
    y = d2dRect.top;
    width = d2dRect.right - d2dRect.left;
    height = d2dRect.bottom - d2dRect.top;
  }

  operator D2D1_RECT_F() const {
    return D2D1::RectF(x, y, x+width, y+height);
  }
};
