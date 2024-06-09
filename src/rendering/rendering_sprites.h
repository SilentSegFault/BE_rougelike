#ifndef RENDERING_SPRITES_H
#define RENDERING_SPRITES_H

#include "../sprite/sprite.h"
#include "../spritesheet/spritesheet.h"

void InitSpriteRenderer();
void DrawSprite(Sprite *sprite, mat4 *projection, int layer, vec2 position, vec2 size, float rotation, int flipX, int flipY);
void DrawSpritesheetFrame(Spritesheet *spritesheet, mat4 *projection, int layer, int row, int frame, vec2 position, vec2 size, float rotation, int flip);
void DisposeSpriteRenderer();

#endif
