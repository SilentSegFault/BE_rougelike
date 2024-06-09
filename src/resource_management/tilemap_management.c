#include "tilemap_management.h"
#include "assets_library.h"
#include "cJSON/cJSON.h"
#include <stdlib.h>
#include "../logger/logger.h"

const char *pathToTilemapsDir;

void SetTilemapsDirPath(const char *path)
{
  pathToTilemapsDir = path;
}

int CreateTilemapLayerFromJson(cJSON *tilemapLayer, int width, int height, TilemapLayer *createdLayer)
{
  cJSON *layer = cJSON_GetObjectItemCaseSensitive(tilemapLayer, "layer");
  cJSON *tileset = cJSON_GetObjectItemCaseSensitive(tilemapLayer, "tileset");
  cJSON *tilesData = cJSON_GetObjectItemCaseSensitive(tilemapLayer, "tilesData");

  if(!cJSON_IsNumber(layer))
  {
    LogTagError("TilemapLoading", "Failed loading tilemap: `layer` should be a number");
    return 0;
  }

  if(!cJSON_IsString(tileset))
  {
    LogTagError("TilemapLoading", "Failed loading tilemap: `tileset` should be a string");
    return 0;
  }

  if(!cJSON_IsArray(tilesData))
  {
    LogTagError("TilemapLoading", "Failed loading tilemap: `tilesData` should be an array");
    return 0;
  }

  int dataSize = cJSON_GetArraySize(tilesData);
  if(dataSize != (width * height))
  {
    LogTagError("TilemapLoading", "Failed loading tilemap: provided data length is diferent than specified");
    return 0;
  }

  int data[dataSize];

  cJSON *tile = NULL;
  int index = 0;
  cJSON_ArrayForEach(tile, tilesData)
  {
    if(!cJSON_IsNumber(tile))
    {
      LogTagWarning("TilemapLoading", "Failed loading tilemap: tiles data should be a number. Empty tile written.");
      data[index] = -1;
      index++;
      continue;
    }

    data[index] = tile->valueint;
    index++;
  }

  *createdLayer = CreateTilemapLayer(*GetTileset(tileset->valuestring), layer->valueint, width, height, data);

  return 1;
}

int LoadTilemapFromJson(cJSON *map, Tilemap *loadedTilemap)
{
  cJSON *width = cJSON_GetObjectItemCaseSensitive(map, "width");
  cJSON *height = cJSON_GetObjectItemCaseSensitive(map, "height");
  cJSON *mapLayers = cJSON_GetObjectItemCaseSensitive(map, "mapLayers");

  if(!cJSON_IsNumber(width))
  {
    LogTagError("TilemapLoading", "Failed loading tilemap: `width` should be a number");
    return 0;
  }

  if(!cJSON_IsNumber(height))
  {
    LogTagError("TilemapLoading", "Failed loading tilemap: `height` should be a number");
    return 0;
  }

  if(!cJSON_IsArray(mapLayers))
  {
    LogTagError("TilemapLoading", "Failed loading tilemap: `mapLayers` should be an array");
    return 0;
  }

  *loadedTilemap = CreateTilemap(width->valueint, height->valueint);

  cJSON *tilemapLayer = NULL;
  cJSON_ArrayForEach(tilemapLayer, mapLayers)
  {
    TilemapLayer createdLayer;
    if(!CreateTilemapLayerFromJson(tilemapLayer, width->valueint, height->valueint, &createdLayer))
    {
      continue;
    }
    AddLayerToTilemap(loadedTilemap, createdLayer);
  }

  if(loadedTilemap->layersCount == 0)
  {
    LogTagError("TilemapLoading", "Failed loading tilemap: no layers created.");
    DisposeTilemap(loadedTilemap);
    return 0;
  }

  return 1;
}
