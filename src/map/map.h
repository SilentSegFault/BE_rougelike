#ifndef MAP_H
#define MAP_H

#include "../tileset/tileset.h"

typedef struct
{
  Tileset tileset;
  int layerVAO;
} MapLayer;

typedef struct
{
  int width;
  int height;
  int layersCount;
  MapLayer *layers;
} Map;

#endif
