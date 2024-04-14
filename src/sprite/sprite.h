/// @file
#ifndef SPRITE_H
#define SPRITE_H

#include "../shader/shader.h"
#include "../texture/texture.h"
#include "cglm/types.h"

typedef struct
{
  Shader shader;
  Texture2D texture;
  vec3 colorMask;
} Sprite;

#endif
