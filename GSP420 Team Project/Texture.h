//Encapsulates a D2D bitmap interface - relates loaded texture for use with Sprite/Plane
//created 5/17 at 17:50 by Richard

#pragma once
#include <d2d1.h>
#include <atlbase.h>
#include <string>

class ImageLoader;

class Texture {
public:
  Texture(const std::wstring filename);

  unsigned getWidth()  const;
  unsigned getHeight() const;

private:
  //This is the COM bitmap object - the payload
  CComPtr<ID2D1Bitmap> comObj;
  //texture dimensions
  D2D1_SIZE_U dims;

  //static imageloader instance for internal usage
  static ImageLoader loader;

  //These classes need access to the COM interface
  friend class Sprite;
  friend class Texture;
};
