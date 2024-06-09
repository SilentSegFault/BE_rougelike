#ifndef SPRITESHEET_MANAGEMENT_H
#define SPRITESHEET_MANAGEMENT_H

#include "../spritesheet/spritesheet.h"
#include "cJSON/cJSON.h"

extern const char *pathToSpritesheetsDir;

void SetSpritesheetsDirPath(const char *path);
int LoadSpritesheetFromJson(cJSON *sprite, Spritesheet *loadedSpritesheet);

#endif
