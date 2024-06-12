#ifndef TEXTURE_MANAGEMENT_H
#define TEXTURE_MANAGEMENT_H

#include "../texture/texture.h"
#include "cJSON/cJSON.h"

extern const char *pathToTexturesDir;

void SetTexturesDirPath(const char *path);
int LoadTexture(const char *file, int alpha, Texture2D *loadedTexture);
int LoadTextureFromJson(cJSON *texture, Texture2D *loadedTexture);

#endif
