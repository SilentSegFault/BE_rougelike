#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "../sprite/sprite.h"
#include "cglm/cglm.h"
#include "pico_headers/pico_ecs.h"

typedef struct
{
  vec2 position;
  vec2 size;
  float rotation;
} Transform;
extern ecs_id_t TransformComp;

typedef struct
{
  Sprite sprite;
  int layer;
} SpriteRender;
extern ecs_id_t SpriteRenderComp;

/// @brief Registers ECS components.
///
/// @param[in] ecs Pointer to ecs context;
void RegisterComponents(ecs_t *ecs);

#endif
