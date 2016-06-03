#pragma once

/*
InputCore
bootstraps input core
contains InputManager object
exposes functions that allow queries about input state
contains UUID map of menu objects
exposes functions that allow management of menu objects
*/

#include "BaseCore.h"
#include "InputManager.h"
#include "MenuManager.h"
#include "GraphicsCore.h"

class InputCore : public BaseCore {
public:
  InputCore(GraphicsCore* gfxCore);

  void Update(float dt) override;

  bool pressed(InputManager::InputKey key); //for checking if the desired key is pressed down at all
  bool pressed(InputManager::InputMouse button);
  bool triggered(InputManager::InputKey key); //for checking if the desired key was initially triggered this frame
  bool triggered(InputManager::InputMouse button);
  bool released(InputManager::InputKey key); //for checking if the desired key was released this frame
  bool released(InputManager::InputMouse button);

  Point GetMouseLocation();
  Point GetMouseDelta();
  bool MouseMoved();

  using UID = unsigned long long;

  UID createMenu();
  //Menu button textures shall consist of three equally sized sub-images stacked vertically.
  //The top image shall be the plain button, the middle the button hovered over, and the
  //bottom the button inits depressed state.
  void addMenubutton(UID menuID, GraphicsCore::UID textureID, GSPRect destRect, GSPMessage buttonMessage);
  void destroyMenu(UID id);

private:
  UID nextID = 1;
  InputManager input;
  std::unordered_map<UID, MenuManager> menus;
  GraphicsCore* gfxCore;

};
