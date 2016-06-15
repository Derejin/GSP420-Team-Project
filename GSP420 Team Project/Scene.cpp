#include "Scene.h"
#include "SharedStore.h"

Scene::Scene(SharedStore* store) :
  store(store),
  menu(store->input)
{
  //nop
}

Scene::~Scene() {
  //nop
}

