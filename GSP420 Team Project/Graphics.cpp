//Central object for graphics; encapsulates renderTarget and D2D factory
//created 5/17 at 17:05PST - Richard

#include "Graphics.h"
#include "GSPWindow.h"
#pragma comment(lib, "d2d1.lib")

Graphics::Graphics(const GSPWindow& window) {
  //factory object is used to generate other interfaces bound to the same context
  HRESULT result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
  assert(SUCCEEDED(result) && "Failed to generate factory.");

  //render-target is the primary object that we're working with. graphics objects will need access to it
  //quite often, hence the linkages to them.
  D2D1_RENDER_TARGET_PROPERTIES targProps = D2D1::RenderTargetProperties();
  D2D_SIZE_U sz = D2D1::SizeU(window.WIDTH, window.HEIGHT);
  D2D1_HWND_RENDER_TARGET_PROPERTIES hTargProps = D2D1::HwndRenderTargetProperties(window.getHandle(), sz);
  result = factory->CreateHwndRenderTarget(targProps, hTargProps, &renderTarget);
  assert(SUCCEEDED(result) && "Failed to create render target.");
}

void Graphics::startDraw() {
  renderTarget->BeginDraw();
  renderTarget->Clear();
}

void Graphics::endDraw() {
  renderTarget->EndDraw();
}
