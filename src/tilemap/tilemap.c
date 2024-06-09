#include "tilemap.h"
#include "glad/glad.h"
#include <stdlib.h>
#include "../logger/logger.h"

Tilemap CreateTilemap(int width, int height)
{
  Tilemap map;

  map.width = width;
  map.height = height;

  map.layersCount = 0;
  map.layers = calloc(1, sizeof(Tilemap));

  return map;
}

TilemapLayer CreateTilemapLayer(Tileset tileset, int drawLayer, int width, int height, int *tileData)
{
  TilemapLayer layer;

  layer.tilesetTexture = tileset.texture;
  layer.drawLayer = drawLayer;

  unsigned int layerVBO;
  glGenBuffers(1, &layerVBO);

  int dataSize = width * height * 6 * 2 * 2;
  float vertexData[dataSize];

  float paddingX = 1.0f / (tileset.tileWidth * tileset.columns);
  float paddingY = 1.0f / (tileset.tileHeight * (tileset.tileCount / tileset.columns));

  int i = 0;
  for(int y = 0; y < height; y++)
  {
    for(int x = 0; x < width; x++)
    {
      int tile = tileData[x + y * width];

      if(tile < 0)
        continue;

      float tx0 = (tile % tileset.columns) * (1.0f / tileset.columns) + paddingX;
      float ty0 = (tile / tileset.columns) * (1.0f / (tileset.tileCount / tileset.columns)) + paddingY;
      float txSize = (1.0f / tileset.columns) - paddingX * 2;
      float tySize = (1.0f / (tileset.tileCount / tileset.columns)) - paddingY * 2;

      // vertex 0 (top left)
      vertexData[i + 0] = x; // position x
      vertexData[i + 1] = y; // position y
      vertexData[i + 2] = tx0; // texcoord x
      vertexData[i + 3] = ty0; // texcoord y
      i += 4;

      // vertex 1 (top right)
      vertexData[i + 0] = x + 1; // position x
      vertexData[i + 1] = y; // position y
      vertexData[i + 2] = tx0 + txSize; // texcoord x
      vertexData[i + 3] = ty0; // texcoord y
      i += 4;

      // vertex 2 (bottom left)
      vertexData[i + 0] = x; // position x
      vertexData[i + 1] = y + 1; // position y
      vertexData[i + 2] = tx0; // texcoord x
      vertexData[i + 3] = ty0 + tySize; // texcoord y
      i += 4;

      // vertex 3 (top right)
      vertexData[i + 0] = x + 1; // position x
      vertexData[i + 1] = y; // position y
      vertexData[i + 2] = tx0 + txSize; // texcoord x
      vertexData[i + 3] = ty0; // texcoord y
      i += 4;

      // vertex 4 (bottom left)
      vertexData[i + 0] = x; // position x
      vertexData[i + 1] = y + 1; // position y
      vertexData[i + 2] = tx0; // texcoord x
      vertexData[i + 3] = ty0 + tySize; // texcoord y
      i += 4;

      // vertex 5 (bottom right)
      vertexData[i + 0] = x + 1; // position x
      vertexData[i + 1] = y + 1; // position y
      vertexData[i + 2] = tx0 + txSize; // texcoord x
      vertexData[i + 3] = ty0 + tySize; // texcoord y
      i += 4;
    }
  }


  unsigned int layerVAO;
  glGenVertexArrays(1, &layerVAO);
  glBindVertexArray(layerVAO);

  glBindBuffer(GL_ARRAY_BUFFER, layerVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(sizeof(float) * 2));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  layer.layerVAO = layerVAO;

  return layer;
}

int AddLayerToTilemap(Tilemap *map, TilemapLayer layer)
{
  TilemapLayer *newLayers = realloc(map->layers, (map->layersCount + 1) * sizeof(TilemapLayer));
  if(newLayers == NULL)
    return 0;

  map->layers = newLayers;
  map->layers[map->layersCount] = layer;
  map->layersCount++;

  return 1;
}

void DisposeTilemap(Tilemap *map)
{
  free(map->layers);
  map->layers = NULL;
  map->layersCount = 0;
}
