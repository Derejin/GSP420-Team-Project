#pragma once

//A DepthBatch object can track any number of RenderObject
//instances, sort them by their z values, and render them in
//their sorted order. This can be used for convenience or to
//effect z sorting.

//Note that DepthBatch does not use owning pointers. When it
//destructs it simply forgets everything. It does not call
//delete on any pointer.

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
