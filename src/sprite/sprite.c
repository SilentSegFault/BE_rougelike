#include "sprite.h"
#include "../logger/logger.h"

Sprite CreateSprite(Shader shader, Texture2D texture, vec3 colorMask)
{
  Sprite sprite;

  sprite.shader = shader;
  sprite.texture = texture;

  sprite.colorMask[0] = colorMask[0];
  sprite.colorMask[1] = colorMask[1];
  sprite.colorMask[2] = colorMask[2];

  return sprite;
}
