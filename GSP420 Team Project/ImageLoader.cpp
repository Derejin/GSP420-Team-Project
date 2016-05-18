//Encapsulates IWICfactory object for shared use, exposing a bitmap loading function
//created 5/17 at 17:26 by Richard

#include "ImageLoader.h"
#include <atlbase.h>
#include <wincodec.h>
#include <d2d1.h>
#include <cassert>
#pragma comment(lib, "Windowscodecs.lib")
#include "Graphics.h"

Graphics* ImageLoader::gfx = nullptr;

ImageLoader::ImageLoader() : factory(nullptr) {
  CoInitialize(NULL); //I hate this crap.

  //the IWIC factory object is used to load textures from various common image formats
  HRESULT result = CoCreateInstance(CLSID_WICImagingFactory1, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&factory);
  assert(SUCCEEDED(result) && "Failed to create IWIC instance.");
}

ImageLoader::~ImageLoader() {
  if(factory) { factory->Release(); }
  CoUninitialize();
}


ID2D1Bitmap* ImageLoader::loadBitmap(const std::wstring& filename) {
  //the order of these is important. objects ina stack frame destruct in reverse of their declaration order
  CComPtr<IWICBitmapDecoder> pDecoder;
  CComPtr<IWICBitmapFrameDecode> pSource;
  CComPtr<IWICFormatConverter> pConverter;

  //this is a little pedantic, but it's more or less self-documenting. it just creates a converter stack for the specific file
  HRESULT result;
  result = factory->CreateDecoderFromFilename(filename.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);
  assert(SUCCEEDED(result) && "Failed to create image decoder.");
  result = pDecoder->GetFrame(0, &pSource);
  assert(SUCCEEDED(result) && "Failed to retrieve frame from image.");
  result = factory->CreateFormatConverter((IWICFormatConverter**)&pConverter);
  assert(SUCCEEDED(result) && "Failed to create image format converter.");
  result = pConverter->Initialize(pSource, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0, WICBitmapPaletteTypeMedianCut);
  assert(SUCCEEDED(result) && "Failed to initialize image converter.");

  //and then we just use the convereter to actually load the image into a D2D bitmap interface
  ID2D1Bitmap* bmp;
  result = gfx->renderTarget->CreateBitmapFromWicBitmap(pConverter, &bmp);
  assert(SUCCEEDED(result) && "Failed to create bitmap.");

  return bmp;
  //the CComPtr's will release the interfaces as the function ends
}
