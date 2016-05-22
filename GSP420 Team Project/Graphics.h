//Central object for graphics; encapsulates renderTarget and D2D factory
//created 5/17 at 17:01PST - Richard

#pragma once
#include <d2d1.h>
#include <atlbase.h>



class GSPWindow;


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

private:
  CComPtr<ID2D1Factory> factory;
  CComPtr<ID2D1HwndRenderTarget> renderTarget;

  friend class Sprite;
  friend class Plane;
  friend class ImageLoader;
  friend class Font;
  friend class Text;

  
  
};
