#ifndef TILESET_H
#define TILESET_H

#include "../texture/texture.h"
#include "cglm/types.h"

typedef struct
{
  Texture2D texture;
  int tileWidth, tileHeight;
  int tileCount;
  int columns;
} Tileset;

Tileset CreateTileset(Texture2D texture, vec2 tileSize, int tileCount, int columns);

#endif
