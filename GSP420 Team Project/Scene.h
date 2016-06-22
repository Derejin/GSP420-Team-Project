#pragma once
#include "MenuManager.h"

struct SharedStore;

//abstract base for all scene classes
//derived classes can be used in the top-level state machine

class Scene {
public:
  //When transitioning to a new scene, simply pass along the store pointer
  //to maintain access to the shared store.
  Scene(SharedStore* store);
  virtual ~Scene();

  //return 'this' to continue the current scene
  //return 'nullptr' to quit the program
  //return a new Scene derivative to switch to it
  virtual Scene* update(float dt) = 0;

  //draw pass for this scene
  //Graphics::begin() and Graphics::end() are called
  //externally and do not need to be invoked here.
  virtual void draw() = 0;

  MenuManager menu;

protected:
  SharedStore* store;

};
