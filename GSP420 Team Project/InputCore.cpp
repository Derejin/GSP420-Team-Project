#define IC_DISABLED
#ifndef IC_DISABLED

#include "InputCore.h"
#include <vector>

InputCore::InputCore(GraphicsCore* gfxCore) : 
  gfxCore(gfxCore), 
  input(gfxCore->window)
{
}

void InputCore::Update(float dt) {
  input.ReadFrame();
  
  std::vector<int> messages;
  if(MouseMoved())                        { messages.push_back(0); }
  if(triggered(InputManager::MOUSE_LEFT)) { messages.push_back(1); }
  if(released(InputManager::MOUSE_LEFT))  { messages.push_back(2); }
  if(triggered(InputManager::KEY_ENTER))  { messages.push_back(3); }
  if(triggered(InputManager::KEY_UP))     { messages.push_back(4); }
  if(triggered(InputManager::KEY_DOWN))   { messages.push_back(5); }

  for(auto& m : menus) {
    for(int msg : messages) { m.second.DecodeMessage(msg); }
    m.second.Update();
  }
}

bool InputCore::pressed(InputManager::InputKey key) {
  return input.IsKeyPressed(key);
}

bool InputCore::pressed(InputManager::InputMouse button) {
  return input.IsMousePressed(button);
}

bool InputCore::triggered(InputManager::InputKey key) {
  return input.IsKeyTriggered(key);
}

bool InputCore::triggered(InputManager::InputMouse button) {
  return input.IsMouseTriggered(button);
}

bool InputCore::released(InputManager::InputKey key) {
  return input.IsKeyReleased(key);
}

bool InputCore::released(InputManager::InputMouse button) {
  return input.IsMouseReleased(button);
}

Point InputCore::GetMouseLocation() {
  return input.GetMouseLocation();
}

Point InputCore::GetMouseDelta() {
  return input.GetMouseDelta();
}

bool InputCore::MouseMoved() {
  return input.MouseMoved();
}

InputCore::UID InputCore::createMenu() {
  UID id = nextID++;
  menus[id] = MenuManager(input);
  gfxCore->batch.addRO(&menus[id]);
  return id;
}
void InputCore::addMenubutton(UID menuID, GraphicsCore::UID textureID, GSPRect destRect, GSPMessage buttonMessage) {
  auto& menu = menus.at(menuID);
  
  Sprite btn;
  btn.setBitmap(gfxCore->textures.at(textureID));
  btn.z = INT_MAX;
  btn.srcRect.height /= 3;
  btn.destRect = destRect;
  
  Sprite hov = btn;
  hov.srcRect.y += hov.srcRect.height;
  Sprite down = hov;
  down.srcRect.y += down.srcRect.height;

  menu.AddButton(btn, hov, down, destRect, buttonMessage);
  gfxCore->batch.addRO(&menu);
}

void InputCore::destroyMenu(UID id) {
  gfxCore->batch.removeRO(&menus.at(id));
  menus.erase(id);
}

#endif
