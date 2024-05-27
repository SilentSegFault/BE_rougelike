#ifndef FONTS_MANAGEMENT_H
#define FONTS_MANAGEMENT_H

#include "../shader/shader.h"
#include "../character/character.h"
#include "cJSON/cJSON.h"

extern const char *pathToFontsDir;

void SetFontsDirPath(const char *path);
int LoadFont(const char *fontPath, int baseHeight, Font *loadedFont);
int LoadFontFromJson(cJSON *font, Font *loadedFont);

#endif
