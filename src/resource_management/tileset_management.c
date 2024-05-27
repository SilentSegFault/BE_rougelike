#include "tileset_management.h"
#include "assets_library.h"
#include <windows.h>
#include "../logger/logger.h"

const char *pathToTilesetsDir;

void SetTilesetDirPath(const char *path)
{
  pathToTilesetsDir = path;
}

int LoadTilesetFromJson(cJSON *tileset, Tileset *loadedTileset)
{
  cJSON *texture = cJSON_GetObjectItemCaseSensitive(tileset, "texture");
  cJSON *alpha = cJSON_GetObjectItemCaseSensitive(tileset, "alpha");
  cJSON *tileWidth = cJSON_GetObjectItemCaseSensitive(tileset, "tileWidth");
  cJSON *tileHeight = cJSON_GetObjectItemCaseSensitive(tileset, "tileHeight");
  cJSON *tileCount = cJSON_GetObjectItemCaseSensitive(tileset, "tileCount");
  cJSON *columns = cJSON_GetObjectItemCaseSensitive(tileset, "columns");

  if(!cJSON_IsString(texture))
  {
    LogTagError("TilesetLoading", "Failed loading tileset: `texture` should be a string");
    return 0;
  }

  if(!cJSON_IsNumber(tileWidth))
  {
    LogTagError("TilesetLoading", "Failed loading tileset: `tileWidth` should be a number");
    return 0;
  }

  if(!cJSON_IsNumber(tileHeight))
  {
    LogTagError("TilesetLoading", "Failed loading tileset: `tileHeight` should be a number");
    return 0;
  }

  if(!cJSON_IsNumber(tileCount))
  {
    LogTagError("TilesetLoading", "Failed loading tileset: `tileCount` should be a number");
    return 0;
  }

  if(!cJSON_IsNumber(columns))
  {
    LogTagError("TilesetLoading", "Failed loading tileset: `columns` should be a number");
    return 0;
  }

  Texture2D tex = *GetTexture2D(texture->valuestring);

  *loadedTileset =  CreateTileset(tex, (vec2) {tileWidth->valueint, tileHeight->valueint}, tileCount->valueint, columns->valueint);

  return 1;
}
