#ifndef TILESET_H
#define TILESET_H

#include "../texture/texture.h"

typedef struct
{
  Texture2D texture;
  int tileWidth, tileHeight;
  int spacing;
  int tileCount;
  int columns;
} Tileset;

#endif
