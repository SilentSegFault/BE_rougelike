#ifndef MAP_MANAGEMENT_H
#define MAP_MANAGEMENT_H

#include "../tilemap/tilemap.h"
#include "cJSON/cJSON.h"

extern const char *pathToTilemapsDir;

void SetTilemapsDirPath(const char *path);
int LoadTilemapFromJson(cJSON *map, Tilemap *loadedTilemap);

#endif
