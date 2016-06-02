//Encapsulates IWICfactory object for shared use, exposing a bitmap loading function
//created 5/17 at 17:26 by Richard

#pragma once
#include <string>

struct ID2D1Bitmap;
struct ID2D1HwndRenderTarget;
struct IWICImagingFactory;
class Graphics;

class ImageLoader {
public:
  ImageLoader();
  ~ImageLoader();

  //invoke this to load a D2D bitmap.
  ID2D1Bitmap* loadBitmap(const std::wstring& filename);

private:
  IWICImagingFactory* factory;

  friend class GraphicsCore;
  static Graphics* gfx; //set in bootstrap

};

