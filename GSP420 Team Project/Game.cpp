#include "Game.h"
#include "TitleScene.h"
#include "MessageHandler.h"

Game::Game() :
	scene(new TitleScene(&store))
{
  //nop
}

void Game::run() {
  timer.getDT();

  while(scene && store.window.update()) {
    store.input.ReadFrame();

    if(store.input.MouseMoved()) { gMessageHandler->HandleMessage(new GSPMessage(store.msgTgt, 0)); }
    if(store.input.IsMouseTriggered(InputManager::MOUSE_LEFT)) { gMessageHandler->HandleMessage(new GSPMessage(store.msgTgt, 1)); }
    if(store.input.IsMouseReleased(InputManager::MOUSE_LEFT))  { gMessageHandler->HandleMessage(new GSPMessage(store.msgTgt, 2)); }
    if(store.input.IsKeyTriggered(InputManager::KEY_ENTER))    { gMessageHandler->HandleMessage(new GSPMessage(store.msgTgt, 3)); }
    if(store.input.IsKeyTriggered(InputManager::KEY_UP))       { gMessageHandler->HandleMessage(new GSPMessage(store.msgTgt, 4)); }
    if(store.input.IsKeyTriggered(InputManager::KEY_DOWN))     { gMessageHandler->HandleMessage(new GSPMessage(store.msgTgt, 5)); }

    Scene* next = scene->update(timer.getDT());

    if(next == scene.get()) {
      store.gfx.startDraw();
      scene->draw();
      store.gfx.endDraw();
    }
    else {
      scene.reset(next);
    }

  }

  if(scene) { scene.reset(nullptr); }
}
