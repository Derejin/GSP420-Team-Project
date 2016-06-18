#define GC_DISABLED
#ifndef GC_DISABLED

#include "GraphicsCore.h"

GraphicsCore::GraphicsCore(std::wstring windowTitle, int width, int height) : 
  window(windowTitle, width, height),
  gfx(window)
{
  Sprite::gfx = ImageLoader::gfx = Font::gfx = &gfx;
  Plane::screenRect = GSPRect(0, 0, (float)window.WIDTH, (float)window.HEIGHT);

}

void GraphicsCore::Update(float dt) {
  flushQueue();

  gfx.startDraw();
  batch.draw();
  gfx.endDraw();
}

GraphicsCore::UID GraphicsCore::createFont(const std::wstring& faceName) {
  UID id = nextUid++;
  fonts[id] = Font(faceName);
  return id;
}

void GraphicsCore::setFontSize(UID fontID, float size) {
  fonts.at(fontID).setSize(size);
}

void GraphicsCore::setFontBold(UID fontID, bool bold) {
  fonts.at(fontID).setBold(bold);
}

void GraphicsCore::setFontItalic(UID fontID, bool italic) {
  fonts.at(fontID).setItalic(italic);
}

void GraphicsCore::setFontColor(UID fontID, ColorF color) {
  fonts.at(fontID).setColor(D2D1::ColorF{color.r, color.g, color.b, color.a});
}

void GraphicsCore::releaseFont(UID id) {
  assert(fonts.erase(id) && "Tried to release non-existent font!");
}

GraphicsCore::UID GraphicsCore::createTexture(const std::wstring& fileName) {
  UID id = nextUid++;
  textures[id] = Texture(fileName);
  return id;
}

unsigned int GraphicsCore::getTextureWidth(UID textureID) {
  return textures.at(textureID).getWidth();
}

unsigned int GraphicsCore::getTextureHeight(UID textureID) {
  return textures.at(textureID).getHeight();
}

void GraphicsCore::releaseTexture(UID id) {
  assert(textures.erase(id) && "Tried to release non-existent texture!");
}

GraphicsCore::UID GraphicsCore::createSprite() {
  UID id = nextUid++;
  sprites[id] = Sprite();
  batch.addRO(&sprites[id]);
  return id;
}

void GraphicsCore::setSpriteTexture(UID spriteID, UID textureID) {
  sprites.at(spriteID).setBitmap(textures.at(textureID));
}

void GraphicsCore::setSpriteOpacity(UID spriteID, float a) {
  sprites.at(spriteID).opacity = a;
}

void GraphicsCore::setSpriteSrcRect(UID spriteID, GSPRect rect) {
  sprites.at(spriteID).srcRect = rect;
}

GSPRect GraphicsCore::getSpriteSrcRect(UID spriteID) {
  return sprites.at(spriteID).srcRect;
}

void GraphicsCore::setSpriteDestRect(UID spriteID, GSPRect rect) {
  sprites.at(spriteID).destRect = rect;
}

GSPRect GraphicsCore::getSpriteDestRect(UID spriteID) {
  return sprites.at(spriteID).destRect;
}

void GraphicsCore::setSpriteDepth(UID spriteID, int z) {
  sprites.at(spriteID).z = z;
}

void GraphicsCore::releaseSprite(UID id) {
  batch.removeRO(&sprites.at(id));
  sprites.erase(id);
}

GraphicsCore::UID GraphicsCore::createPlane() {
  UID id = nextUid++;
  planes[id] = Plane();
  batch.addRO(&planes[id]);
  return id;
}

void GraphicsCore::setPlaneTexture(UID planeID, UID textureID) {
  planes.at(planeID).setTexture(textures.at(textureID));
}

void GraphicsCore::setPlaneOpacity(UID planeID, float a) {
  planes.at(planeID).opacity = a;
}

void GraphicsCore::setPlaneSrcRect(UID planeID, GSPRect rect) {
  planes.at(planeID).srcRect = rect;
}

GSPRect GraphicsCore::getPlaneSrcRect(UID planeID) {
  return planes.at(planeID).srcRect;
}

void GraphicsCore::setPlaneScroll(UID planeID, float x, float y) {
  planes.at(planeID).scrollx = x;
  planes.at(planeID).scrolly = y;
}

void GraphicsCore::setPlaneScrollRelative(UID planeID, float dx, float dy) {
  planes.at(planeID).scrollx += dx;
  planes.at(planeID).scrolly += dy;
}

void GraphicsCore::setPlaneDepth(UID planeID, int z) {
  planes.at(planeID).z = z;
}

void GraphicsCore::releasePlane(UID id) {
  batch.removeRO(&planes.at(id));
  planes.erase(id);
}

GraphicsCore::UID GraphicsCore::createText(const std::wstring& string, UID fontID) {
  UID id = nextUid++;
  texts[id] = Text(string, &fonts.at(fontID));
  batch.addRO(&texts[id]);
  return id;
}

void GraphicsCore::setTextRect(UID textID, GSPRect rect) {
  texts.at(textID).setRect(rect);
}

void GraphicsCore::setTextFont(UID textID, UID fontID) {
  texts.at(textID).setFont(&fonts.at(fontID));
}

void GraphicsCore::setTextString(UID textID, const std::wstring& string) {
  texts.at(textID).setString(string);
}

void GraphicsCore::setTextDepth(UID textID, int z) {
  texts.at(textID).z = z;
}

void GraphicsCore::releaseText(UID id) {
  batch.removeRO(&texts.at(id));
  texts.erase(id);
}

void GraphicsCore::flushQueue(){
  CopyMessage(); //transfers all messages from incoming (mutexed) queue to buffer queue

  while(!m_QueueBuffer.empty()) {
    executeAndDeleteMessage(m_QueueBuffer.front());
    m_QueueBuffer.pop();
  }
}

void GraphicsCore::executeAndDeleteMessage(SMessage* msg) {

  //~ ~_ message processing goeth here

  delete msg;
}

#endif
