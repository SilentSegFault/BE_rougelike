/// @file
#ifndef TEXTURE_H
#define TEXTURE_H

/// Stores config data for textures.
typedef struct
{
  int width, height;
  unsigned int internalFormat;
  unsigned int imageFormat;
  unsigned int wrapS, wrapT;
  unsigned int filterMin, filterMax;
} Texture2DConfig;

/// Handle to texture.
typedef unsigned int Texture2D;

/// @brief Generates Texture2D
///
/// Using image source/data and specified config generates Texture2D.
///
/// @param[in] imgData Image data/source
/// @parma[in] config Configuration for texture.
/// @returns Generated Texture2D handle.
Texture2D GenerateTexture(unsigned char *imgData, Texture2DConfig *config);
/// @brief Binds specified texture to be used.
///
/// @param[in] texture Texture2D handle to be used.
void BindTexture(Texture2D texture);

#endif
