#include "SharedStore.h"
#include "MessageHandler.h"

SharedStore::SharedStore() :
  window(L"Run, Man, Run!", screenWidth, screenHeight),
  gfx(window),
  input(window),
  rng(std::random_device{}())
{
  gMessageHandler->Instantiate();
}
