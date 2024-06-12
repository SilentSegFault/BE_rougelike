#ifndef ANIMATION_H
#define ANIMATION_H

#include "../spritesheet/spritesheet.h"

typedef struct
{
  Spritesheet *spritesheet;
  int row;
  int frames;
  int speed;
} Animation;

Animation CreateAnimation(Spritesheet *spritesheet, int row, int frames, int speed);

#endif
