#ifndef SHADER_MANAGEMENT_H
#define SHADER_MANAGEMENT_H

#include "../shader/shader.h"
#include "cJSON/cJSON.h"

extern const char *pathToShadersDir;

void SetShadersDirPath(const char *path);
int LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, Shader *loadedShader);
int LoadShaderFromJson(cJSON *shader, Shader *loadedShader);

#endif
