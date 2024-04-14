#include "texture.h"
#include "glad/glad.h"

Texture2D GenerateTexture(unsigned char *imgData, Texture2DConfig *config)
{
  Texture2D texture;
  glGenTextures(1, &texture);

  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, config->internalFormat, config->width,
               config->height, 0, config->imageFormat, GL_UNSIGNED_BYTE, imgData);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, config->wrapS);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, config->wrapT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, config->filterMin);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, config->filterMax);

  glBindTexture(GL_TEXTURE_2D, 0);

  return texture;
}

void BindTexture(Texture2D texture)
{
  glBindTexture(GL_TEXTURE_2D, texture);
}
