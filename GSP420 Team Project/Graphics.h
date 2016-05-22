//Central object for graphics; encapsulates renderTarget and D2D factory
//created 5/17 at 17:01PST - Richard

#pragma once
#include <d2d1.h>
#include <atlbase.h>
#include"ImageLoader.h"// had to include for sprites and using image loader based off demo
#include <vector>//needed to include for sprites

class GSPWindow;
class Bitmap;// Needed this to work on sprites subject to change

class Graphics {
	friend class Sprite;// needed this to work on sprites/subject to removal later
public:
  //constructor - render target will be sized to match window's user-area
  //remember to bind the object to its subordinate classes during bootstrap
  Graphics(const GSPWindow& window);

  //starts draw pass and clears RT
  void startDraw();

  //finishes draw pass
  void endDraw();

  Sprite createSprite();// For testing sprites/subject to change

  Bitmap loadImageFromFile(const std::wstring& filename);//For testing sprites/loading files

private:
  CComPtr<ID2D1Factory> factory;
  CComPtr<ID2D1HwndRenderTarget> renderTarget;

  friend class Sprite;
  friend class Plane;
  friend class ImageLoader;
  friend class Font;
  friend class Text;

  std::vector<Sprite*> sprites;//needed to add this to handle the batching for sprites following the demo (CB)
  ImageLoader loader;// For working on sprites/testing. subject to removal later
};
