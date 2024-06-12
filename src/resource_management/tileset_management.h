#ifndef TILESET_MANAGEMENT_H
#define TILESET_MANAGEMENT_H

#include "../tileset/tileset.h"
#include "cJSON/cJSON.h"

extern const char *pathToTilesetsDir;

void SetTilesetDirPath(const char *path);
int LoadTilesetFromJson(cJSON *tileset, Tileset *loadedTileset);

#endif
