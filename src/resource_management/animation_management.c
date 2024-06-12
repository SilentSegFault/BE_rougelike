#include "animation_management.h"
#include "assets_library.h"
#include "cJSON/cJSON.h"
#include "../logger/logger.h"

const char *pathToAnimationsDir;

void SetAnimationsDirPath(const char *path)
{
  pathToAnimationsDir = path;
}

int LoadAnimationFromJson(cJSON *sprite, Animation *loadedAnimation)
{
  cJSON *spritesheet = cJSON_GetObjectItemCaseSensitive(sprite, "spritesheet");
  cJSON *row = cJSON_GetObjectItemCaseSensitive(sprite, "row");
  cJSON *frames = cJSON_GetObjectItemCaseSensitive(sprite, "frames");
  cJSON *speed = cJSON_GetObjectItemCaseSensitive(sprite, "speed");

  if(!cJSON_IsString(spritesheet))
  {
    LogTagError("AnimationLoading", "Error loading animation! `spritesheet` should be a string!");
    return 0;
  }

  if(!cJSON_IsNumber(row))
  {
    LogTagError("AnimationLoading", "Error loading animation! `row` should be a number!");
    return 0;
  }

  if(!cJSON_IsNumber(frames))
  {
    LogTagError("AnimationLoading", "Error loading animation! `frames` should be a number!");
    return 0;
  }

  if(!cJSON_IsNumber(speed))
  {
    LogTagError("AnimationLoading", "Error loading animation! `speed` should be a number!");
    return 0;
  }

  *loadedAnimation = CreateAnimation(GetSpritesheet(spritesheet->valuestring),
                                     row->valueint,
                                     frames->valueint,
                                     speed->valueint);

  return 1;
}
