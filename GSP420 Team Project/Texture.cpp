//Created 5/17 at 17:50 by Richard

#include "Texture.h"
#include "ImageLoader.h"
#include "Graphics.h"

ImageLoader Texture::loader;

Texture::Texture(const std::wstring filename) : comObj(loader.loadBitmap(filename)) {
  dims = comObj->GetPixelSize();
}

unsigned Texture::getWidth() const {
  return dims.width;
}

unsigned Texture::getHeight() const {
  return dims.height;
}
