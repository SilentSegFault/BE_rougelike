#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "../texture/texture.h"

typedef struct
{
  Texture2D texture;
  int rows;
  int cols;
  int frameWidth;
  int frameHeight;
} Spritesheet;

Spritesheet CreateSpritesheet(Texture2D texture, int rows, int cols, int frameWidth, int frameHeight);

#endif
