#ifndef SPRITE_MANAGEMENT_H
#define SPRITE_MANAGEMENT_H

#include "../sprite/sprite.h"
#include "cJSON/cJSON.h"

extern const char *pathToSpritesDir;

void SetSpritesDirPath(const char *path);
int LoadSpriteFromJson(cJSON *sprite, Sprite *loadedSprite);

#endif
