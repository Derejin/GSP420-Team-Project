#pragma once

#include "RenderObject.h"
#include <vector>

class DepthBatch {
public:
  void draw();
  void addRO(RenderObject* obj);
  void removeRO(RenderObject* obj);

private:
  void sort();
  std::vector<RenderObject*> list;

};
