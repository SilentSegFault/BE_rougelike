#ifndef RENDERING_SPRITES_H
#define RENDERING_SPRITES_H

#include "../sprite/sprite.h"

void InitSpriteRenderer();
void DrawSprite(Sprite *sprite, mat4 *projection, vec2 position, vec2 size, float rotation, int flipX, int flipY);
void DisposeSpriteRenderer();

#endif
