#pragma once
#include "MenuManager.h"

struct SharedStore;

class Scene {
public:
  Scene(SharedStore* store);
  virtual ~Scene();
  virtual Scene* update(float dt) = 0;
  virtual void draw() = 0;

  MenuManager menu;

protected:
  SharedStore* store;

};
