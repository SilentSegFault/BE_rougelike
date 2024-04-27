#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "../sprite/sprite.h"
#include "cglm/cglm.h"
#include "flecs/flecs.h"
#include "../window/win32_helper.h"

typedef struct
{
  vec2 position;
  vec2 size;
  float rotation;
}
Transform;

typedef struct
{
  Sprite sprite;
  int layer;
} SpriteRender;

typedef struct
{
  float health;
  float damage;
  float moveSpeed;
  float range;
} Stats;

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

typedef struct
{
  vec2 direction;
  float speed;
  float maxDistance;
} Projectile;

extern ECS_COMPONENT_DECLARE(Transform);
extern ECS_COMPONENT_DECLARE(SpriteRender);
extern ECS_COMPONENT_DECLARE(Stats);
extern ECS_COMPONENT_DECLARE(PlayerController);
extern ECS_COMPONENT_DECLARE(Projectile);

void ComponentsImport(ecs_world_t *world);

#endif
