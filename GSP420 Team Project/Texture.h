#pragma once
#include <d2d1.h>
#include <atlbase.h>
#include <string>

//This class encapsulates a loaded texture for use with the
//Sprite and/or Plane classes. Mutliple Sprites and Planes
//can share the same Texture object safely.

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
  friend class Plane;
};
