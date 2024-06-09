#include "spritesheet_management.h"
#include "assets_library.h"
#include "cJSON/cJSON.h"
#include "../logger/logger.h"

const char *pathToSpritesheetsDir;

void SetSpritesheetsDirPath(const char *path)
{
  pathToSpritesheetsDir = path;
}

int LoadSpritesheetFromJson(cJSON *sprite, Spritesheet *loadedSpritesheet)
{
  cJSON *texture = cJSON_GetObjectItemCaseSensitive(sprite, "texture");
  cJSON *rows = cJSON_GetObjectItemCaseSensitive(sprite, "rows");
  cJSON *cols = cJSON_GetObjectItemCaseSensitive(sprite, "cols");
  cJSON *frameWidth = cJSON_GetObjectItemCaseSensitive(sprite, "frameWidth");
  cJSON *frameHeight = cJSON_GetObjectItemCaseSensitive(sprite, "frameHeight");

  if(!cJSON_IsString(texture))
  {
    LogTagError("SpritesheetLoading", "Error loading spritesheet! `texture` should be a string!");
    return 0;
  }

  if(!cJSON_IsNumber(rows))
  {
    LogTagError("SpritesheetLoading", "Error loading spritesheet! `rows` should be a number!");
    return 0;
  }

  if(!cJSON_IsNumber(cols))
  {
    LogTagError("SpritesheetLoading", "Error loading spritesheet! `cols` should be a number!");
    return 0;
  }

  if(!cJSON_IsNumber(frameWidth))
  {
    LogTagError("SpritesheetLoading", "Error loading spritesheet! `frameWidth` should be a number!");
    return 0;
  }

  if(!cJSON_IsNumber(frameHeight))
  {
    LogTagError("SpritesheetLoading", "Error loading spritesheet! `frameHeight` should be a number!");
    return 0;
  }

  *loadedSpritesheet = CreateSpritesheet(*GetTexture2D(texture->valuestring),
                                         rows->valueint,
                                         cols->valueint,
                                         frameWidth->valueint,
                                         frameHeight->valueint);

  return 1;
}
