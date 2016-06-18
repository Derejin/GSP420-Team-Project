//created by colton on 5/20

#include "Graphics.h"
#include "Plane.h"

GSPRect Plane::screenRect;

void Plane::setTexture(Texture& texture) {
  srcRect = GSPRect(0, 0, (float)texture.getWidth(), (float)texture.getHeight());
  for(auto& spr : sprites) { spr.setBitmap(texture); }
}

void Plane::draw() {
  if(scrollx < 0) { scrollx += screenRect.width;  }
  if(scrolly < 0) { scrolly += screenRect.height; }
  if(scrollx > screenRect.width ) { scrollx -= screenRect.width;  }
  if(scrolly > screenRect.height) { scrolly -= screenRect.height; }

  sprites[0].destRect = screenRect;
  sprites[0].destRect.x = -scrollx;
  sprites[0].destRect.y = -scrolly;

  sprites[1].destRect = sprites[0].destRect;
  sprites[1].destRect.x += screenRect.width - 1;

  sprites[2].destRect = sprites[0].destRect;
  sprites[2].destRect.y += screenRect.height;

  sprites[3].destRect = sprites[0].destRect;
  sprites[3].destRect.x += screenRect.width;
  sprites[3].destRect.y += screenRect.height;

  for(auto& spr : sprites) { spr.draw(); }
}
