/// @file
#ifndef RENDERING_SPRITES_H
#define RENDERING_SPRITES_H

#include "../sprite/sprite.h"

/// @brief Initializes resources for SpriteRenderer
void InitSpriteRenderer();
/// @brief Draws Sprite
///
/// @param sprite Sprite that will be drawn.
/// @param position Drawing position of sprites left top corner.
/// @param size Sprite size in pixels.
/// @param rotation Sprite rotation in degrees.
void DrawSprite(Sprite sprite, vec2 position, vec2 size, float rotation);
/// @brief Disposes resources allocated in InitSpriteRenderer(Shader shader).
void DisposeSpriteRenderer();

#endif
