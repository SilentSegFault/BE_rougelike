#include "tileset.h"

Tileset CreateTileset(Texture2D texture, vec2 tileSize, int tileCount, int columns)
{
  Tileset tileset;

  tileset.texture = texture;
  tileset.tileWidth = tileSize[0];
  tileset.tileHeight = tileSize[1];
  tileset.tileCount = tileCount;
  tileset.columns = columns;

  return tileset;
}
