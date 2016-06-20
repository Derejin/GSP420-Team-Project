#include "Game.h"
#include "TitleScene.h"
#include "MessageHandler.h"

Game::Game() :
	scene(new TitleScene(&store)),
  fadeTex(L"Texture/Planes/black.png")
{
  fader.setTexture(fadeTex);
  fader.opacity = 0;
}

void Game::run() {
  timer.getDT();
  scene->update(0);
  fadeIn();

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
    else { //changed to new scene, so do fadey stuff
      fadeOut();

      scene.reset(next);
      if(!scene) { break; }
      scene->update(0);

      fadeIn();
    }

  }

  if(scene) { scene.reset(nullptr); }
}

void Game::fadeOut() {
  float fadeTimer = 0;
  while((fadeTimer < FADE_DURATION) && store.window.update()) {
    fader.opacity = fadeTimer / FADE_DURATION;
    store.bgm->setVolume((1.0f - fader.opacity) * store.oldBaseVol);

    store.gfx.startDraw();
    scene->draw();
    fader.draw();
    store.gfx.endDraw();

    fadeTimer += timer.getDT();
  }
  store.bgm->setVolume(0);
}

void Game::fadeIn() {
  store.bgm.reset(new Song(store.songPath, 0.1f));

  float fadeTimer = FADE_DURATION;
  while(store.window.update()) {
    fadeTimer -= timer.getDT();
    if(fadeTimer <= 0) { break; }

    fader.opacity = fadeTimer / FADE_DURATION;
    store.bgm->setVolume((1.0f - fader.opacity) * store.songBaseVol);

    store.gfx.startDraw();
    scene->draw();
    fader.draw();
    store.gfx.endDraw();
  }
  store.bgm->setVolume(store.songBaseVol);
}
