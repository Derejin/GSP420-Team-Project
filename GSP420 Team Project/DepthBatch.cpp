#include "DepthBatch.h"
#include <algorithm>

void DepthBatch::draw() {
  sort();
  for(auto ro : list) { ro->draw(); }
}

void DepthBatch::addRO(RenderObject* obj) {
  list.push_back(obj);
}

void DepthBatch::removeRO(RenderObject* obj) {
  list.erase(std::remove(list.begin(), list.end(), obj), list.end());
}

void DepthBatch::sort() {
  std::sort(list.begin(), list.end(), [](RenderObject* a, RenderObject* b) { return a->z < b->z; });
}
