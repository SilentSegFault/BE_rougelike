#include "shader_management.h"
#include "../utility/loadFileSource.h"
#include "../logger/logger.h"
#include <stdio.h>

const char *pathToShadersDir;

void SetShadersDirPath(const char *path)
{
  pathToShadersDir = path;
}

int LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, Shader *loadedShader)
{
  char *vertexSource = LoadFileSource(vShaderFile);
  if(vertexSource == NULL)
  {
    LogTagError("ShaderLoading", "Couldn't load vertex shader source.");
    return 0;
  }

  char *fragmentSource = LoadFileSource(fShaderFile);
  if(fragmentSource == NULL)
  {
    LogTagError("ShaderLoading", "Couldn't load fragment shader source.");
    return 0;
  }

  char *geometrySource = NULL;
  if(gShaderFile != NULL)
  {
    geometrySource = LoadFileSource(gShaderFile);
    if(geometrySource == NULL)
    {
      LogTagError("ShaderLoading", "Couldn't load geometry shader source.");
      return 0;
    }
  }

  if(!CompileShader(vertexSource, fragmentSource, geometrySource, loadedShader))
  {
    LogTagError("ShaderLoading", "Couldn't compile shader.");
    return 0;
  }
  free(vertexSource);
  free(fragmentSource);
  free(geometrySource);

  return 1;
}

int LoadShaderFromJson(cJSON *shader, Shader *loadedShader)
{
  cJSON *vertexSource = cJSON_GetObjectItemCaseSensitive(shader, "vertexSource");
  cJSON *fragmentSource = cJSON_GetObjectItemCaseSensitive(shader, "fragmentSource");
  cJSON *geometrySource = cJSON_GetObjectItemCaseSensitive(shader, "geometrySource");

  if(!cJSON_IsString(vertexSource))
  {
    LogTagError("ShaderLoading", "Error loading shader! `vertexSource` should be a string!");
    return 0;
  }

  if(!cJSON_IsString(fragmentSource))
  {
    LogTagError("ShaderLoading", "Error loading shader! `fragmentSource` should be a string!");
    return 0;
  }

  char vShaderFile[MAX_PATH];
  char fShaderFile[MAX_PATH];
  char gShaderFile[MAX_PATH];

  sprintf_s(vShaderFile, MAX_PATH, "%s/%s", pathToShadersDir, vertexSource->valuestring);
  sprintf_s(fShaderFile, MAX_PATH, "%s/%s", pathToShadersDir, fragmentSource->valuestring);
  if(cJSON_IsString(geometrySource))
  {
    sprintf_s(gShaderFile, MAX_PATH, "%s/%s", pathToShadersDir, geometrySource->valuestring);
    if(!LoadShader(vShaderFile, fShaderFile, gShaderFile, loadedShader))
      return 0;
  }
  else
  {
    if(!LoadShader(vShaderFile, fShaderFile, NULL, loadedShader))
      return 0;
  }

  return 1;
}
