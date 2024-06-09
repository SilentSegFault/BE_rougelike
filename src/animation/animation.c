#include "animation.h"

Animation CreateAnimation(Spritesheet *spritesheet, int row, int frames, int speed)
{
  Animation animation = {0};

  animation.spritesheet = spritesheet;
  animation.row = row;
  animation.frames = frames;
  animation.speed = speed;

  return animation;
}
