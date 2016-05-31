#pragma once

class RenderObject {
public:
  virtual ~RenderObject() {}

  virtual void draw() = 0;
  int z = 0;
};
