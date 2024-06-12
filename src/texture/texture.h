#ifndef TEXTURE_H
#define TEXTURE_H

typedef struct
{
  int width, height;
  unsigned int internalFormat;
  unsigned int imageFormat;
  unsigned int wrapS, wrapT;
  unsigned int filterMin, filterMax;
} Texture2DConfig;

typedef unsigned int Texture2D;

int GenerateTexture(unsigned char *imgData, Texture2DConfig *config, Texture2D *generatedTexture);
void BindTexture(Texture2D texture);

#endif
