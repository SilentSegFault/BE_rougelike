#include "texture_management.h"
#include <windows.h>
#include "stb/stb_image.h"
#include "glad/glad.h"
#include "../logger/logger.h"

const char *pathToTexturesDir;

void SetTexturesDirPath(const char *path)
{
  pathToTexturesDir = path;
}

int LoadTexture(const char *file, int alpha, Texture2D *loadedTexture)
{
  Texture2DConfig config = {0};

  config.width          = 0;
  config.height         = 0;
  config.internalFormat = GL_RGB;
  config.imageFormat    = GL_RGB;
  config.wrapS          = GL_CLAMP;
  config.wrapT          = GL_CLAMP;
  config.filterMin      = GL_NEAREST;
  config.filterMax      = GL_NEAREST;

  if(alpha)
  {
    config.internalFormat = GL_RGBA;
    config.imageFormat = GL_RGBA;
  }

  int iNrChannels;
  unsigned char *data = stbi_load(file, &config.width, &config.height, &iNrChannels, 0);

  if(data == NULL)
  {
    LogTagError("TextureLoading", "Couldn't load texture data.");
    return 0;
  }

  if(!GenerateTexture(data, &config, loadedTexture))
  {
    LogTagError("TextureLoading", "Couldn't load texture.");
    return 0;
  }
  
  stbi_image_free(data);

  return 1;
}

int LoadTextureFromJson(cJSON *texture, Texture2D *loadedTexture)
{
  cJSON *source = cJSON_GetObjectItemCaseSensitive(texture, "source");
  cJSON *alpha = cJSON_GetObjectItemCaseSensitive(texture, "alpha");

  if(!cJSON_IsString(source))
  {
    LogTagError("TextureLoading", "Error loading texture! `source` should be a string!");
    return 0;
  }

  if(!cJSON_IsBool(alpha))
  {
    LogTagError("TextureLoading", "Error loading texture! `alpha` should be a boolean!");
    return 0;
  }

  char sourceFilePath[MAX_PATH];
  sprintf_s(sourceFilePath, MAX_PATH, "%s/%s", pathToTexturesDir, source->valuestring);

  BOOL alphaValue = cJSON_IsTrue(alpha);

  if(!LoadTexture(sourceFilePath, alphaValue, loadedTexture))
  {
    return 0;
  }

  return 1;
}
