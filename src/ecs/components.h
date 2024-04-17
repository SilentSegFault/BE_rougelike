#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "../sprite/sprite.h"
#include "cglm/cglm.h"
#include "pico_headers/pico_ecs.h"
#include "../window/win32_helper.h"

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

typedef struct
{
  float health;
  float damage;
  float moveSpeed;
  float range;
} Stats;
extern ecs_id_t StatsComp;

typedef struct
{
  struct
  {
    Key moveUp;
    Key moveDown;
    Key moveLeft;
    Key moveRight;
    Key shoot;
  } Keys;
} PlayerController;
extern ecs_id_t PlayerControllerComp;

typedef struct
{
  vec2 direction;
  float speed;
  float maxDistance;
} Projectile;
extern ecs_id_t ProjectileComp;

typedef struct
{
  vec2 offset;
  vec2 size;
} BoxCollider;
extern ecs_id_t BoxColliderComp;

/// @brief Registers ECS components.
///
/// @param[in] ecs Pointer to ecs context;
void RegisterComponents(ecs_t *ecs);

#endif
