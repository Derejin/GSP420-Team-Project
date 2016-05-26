#pragma once

class RenderObject {
public:
  virtual void draw() = 0;
  int z = 0;
};
