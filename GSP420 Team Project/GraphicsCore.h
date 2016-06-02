#pragma once
#include "BaseCore.h"
#include "GSPWindow.h"
#include "Graphics.h"
#include "ImageLoader.h"
#include "DepthBatch.h"
#include <unordered_map>
#include "Font.h"
#include "Texture.h"
#include "Plane.h"
#include "Sprite.h"
#include "Text.h"

//This is absolutely the stupidest thing I've ever coded. >:|

class GraphicsCore : public BaseCore {
public:
  GraphicsCore(std::wstring windowTitle, int width, int height);
  void Update(float dt); //flush message queue and render

  using UID = unsigned long long;

  struct ColorF { float r, g, b, a; };

  UID createFont(const std::wstring& faceName);
  void setFontSize(UID fontID, float size);
  void setFontBold(UID fontID, bool bold);
  void setFontItalic(UID fontID, bool italic);
  void setFontColor(UID fontID, ColorF color);
  void releaseFont(UID id);

  UID createTexture(const std::wstring& fileName);
  unsigned int getTextureWidth(UID textureID);
  unsigned int getTextureHeight(UID textureID);
  void releaseTexture(UID id);

  UID createSprite();
  void setSpriteTexture(UID spriteID, UID textureID);
  void setSpriteOpacity(UID spriteID, float a); //range 0.0f to 1.0f
  void setSpriteSrcRect(UID spriteID, GSPRect rect);
  GSPRect getSpriteSrcRect(UID spriteID);
  void setSpriteDestRect(UID spriteID, GSPRect rect);
  GSPRect getSpriteDestRect(UID spriteID);
  void setSpriteDepth(UID spriteID, int z);
  void releaseSprite(UID id);

  UID createPlane();
  void setPlaneTexture(UID planeID, UID textureID);
  void setPlaneOpacity(UID planeID, float a); //range 0.0f to 1.0f
  void setPlaneSrcRect(UID planeID, GSPRect rect);
  GSPRect getPlaneSrcRect(UID planeID);
  void setPlaneScroll(UID planeID, float x, float y);
  void setPlaneScrollRelative(UID planeID, float dx, float dy);
  void setPlaneDepth(UID planeID, int z);
  void releasePlane(UID id);

  UID createText(const std::wstring& string, UID fontID);
  void setTextRect(UID textID, GSPRect rect);
  void setTextFont(UID textID, UID fontID);
  void setTextString(UID textID, const std::wstring& string);
  void setTextDepth(UID textID, int z);
  void releaseText(UID id);


private:
  void flushQueue();
  void executeAndDeleteMessage(SMessage* msg);

  GSPWindow window;
  Graphics gfx;
  ImageLoader imgLoader;
  DepthBatch batch;

  UID nextUid = 1;
  std::unordered_map<UID, Font> fonts;
  std::unordered_map<UID, Texture> textures;
  std::unordered_map<UID, Sprite> sprites;
  std::unordered_map<UID, Plane> planes;
  std::unordered_map<UID, Text> texts;

};

