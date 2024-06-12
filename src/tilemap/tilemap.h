#ifndef MAP_H
#define MAP_H

#include "../tileset/tileset.h"

typedef struct
{
  Texture2D tilesetTexture;
  int layerVAO;
  int drawLayer;
} TilemapLayer;

typedef struct
{
  int width;
  int height;
  int layersCount;
  TilemapLayer *layers;
} Tilemap;

Tilemap CreateTilemap(int width, int height);
TilemapLayer CreateTilemapLayer(Tileset tileset, int drawLayer, int width, int height, int *tileData);
int AddLayerToTilemap(Tilemap *map, TilemapLayer layer);
void DisposeTilemap(Tilemap *map);


#endif
