#include "sprite_management.h"
#include "assets_library.h"
#include "cJSON/cJSON.h"
#include "../logger/logger.h"

const char *pathToSpritesDir;

void SetSpritesDirPath(const char *path)
{
  pathToSpritesDir = path;
}

int LoadSpriteFromJson(cJSON *sprite, Sprite *loadedSprite)
{
  cJSON *shaderName = cJSON_GetObjectItemCaseSensitive(sprite, "shader");
  cJSON *textureName = cJSON_GetObjectItemCaseSensitive(sprite, "texture");
  cJSON *colorMask = cJSON_GetObjectItemCaseSensitive(sprite, "colorMask");

  if(!cJSON_IsString(shaderName))
  {
    LogTagError("SpriteLoading", "Error loading sprite! `shader` should be a string!");
    return 0;
  }

  if(!cJSON_IsString(textureName))
  {
    LogTagError("SpriteLoading", "Error loading sprite! `texture` should be a string!");
    return 0;
  }


  if(!cJSON_IsArray(colorMask))
  {
    LogTagError("SpriteLoading", "Error loading sprite! `colorMask` should be an array!");
    return 0;
  }

  if(cJSON_GetArraySize(colorMask) != 3)
  {
    LogTagError("SpriteLoading", "Error loading sprite! `colorMask` should have 3 values!");
    return 0;
  }
  
  cJSON *r = cJSON_GetArrayItem(colorMask, 0);
  cJSON *g = cJSON_GetArrayItem(colorMask, 1);
  cJSON *b = cJSON_GetArrayItem(colorMask, 2);

  if(!cJSON_IsNumber(r) || !cJSON_IsNumber(r) || !cJSON_IsNumber(r))
  {
    LogTagError("SpriteLoading", "Error loading sprite! values in `colorMask` array should be numbers");
    return 0;
  }

  *loadedSprite = CreateSprite(*GetShader(shaderName->valuestring), *GetTexture2D(textureName->valuestring), 
                               (vec3){r->valuedouble, g->valuedouble, b->valuedouble});

  return 1;
}
