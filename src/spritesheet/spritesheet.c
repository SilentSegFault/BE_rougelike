#include "spritesheet.h"

Spritesheet CreateSpritesheet(Texture2D texture, int rows, int cols, int frameWidth, int frameHeight)
{
  Spritesheet spritesheet = {0};

  spritesheet.texture = texture;
  spritesheet.rows = rows;
  spritesheet.cols = cols;
  spritesheet.frameWidth = frameWidth;
  spritesheet.frameHeight = frameHeight;

  return spritesheet;
}
