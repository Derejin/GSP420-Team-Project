#pragma once

//This is a base object for renderable objects.
//The z member is only used for sorting within a DepthBatch
//object. Otherwise drawing is in explicit order.

class RenderObject {
public:
  virtual ~RenderObject() {}

  virtual void draw() = 0;
  int z = 0;
};
