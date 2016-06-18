#include "SharedStore.h"
#include "MessageHandler.h"

SharedStore::SharedStore() :
  window(L"Testing Window", screenWidth, screenHeight),
  gfx(window),
  input(window),
  rng(std::random_device{}())
{
  gMessageHandler->Instantiate();
}
