#pragma once
#include <d2d1.h>
#include <vector>
#include <deque>

//this header contains general utilities.

//simple 2D float vector
struct vec2f {
  float x, y;

  vec2f operator+(vec2f other) {
    return vec2f{x + other.x, y + other.y};
  }

  vec2f operator+=(vec2f other) {
    *this = *this + other;
    return *this;
  }

  vec2f operator*(float scale) {
    return vec2f{x * scale, y * scale};
  }
};

//A rect expressed as x/y/width/height for convenience.
//It converts automatically to and from D2D1_RECT_F.
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

  void moveBy(vec2f vec) {
    x += vec.x;
    y += vec.y;
  }

  void moveTo(vec2f vec) {
    x = vec.x;
    y = vec.y;
  }

  std::vector<GSPRect> testOverlap(const std::vector<GSPRect>& colliders) {
    std::vector<GSPRect> hits;

    for(auto c : colliders) {
      if(testOverlap(c)) { hits.push_back(c); }
    }

    return hits;
  }

  bool testOverlap(GSPRect other) {
    D2D1_RECT_F a = *this;
    D2D1_RECT_F b = other;

    if(a.top > b.bottom) { return false; }
    if(a.left > b.right) { return false; }
    if(a.bottom < b.top) { return false; }
    if(a.right < b.left) { return false; }

    return true;
  }
};

