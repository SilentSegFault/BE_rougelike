#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "../sprite/sprite.h"
#include "cglm/cglm.h"
#include "flecs/flecs.h"
#include "../window/win32_helper.h"
#include "cute_headers/cute_c2.h"

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

typedef enum
{
  CT_CIRCLE = 0,
  CT_CAPSULE,
  CT_AABB,
  CT_POLY
} ColliderType;

typedef struct
{
  ColliderType type;
  union
  {
    c2Circle circleCollider;
    c2Capsule capsuleCollider;
    c2AABB AABBCollider;
    c2Poly polyCollider;
  };
} Collider;

extern ECS_COMPONENT_DECLARE(Transform);
extern ECS_COMPONENT_DECLARE(SpriteRender);
extern ECS_COMPONENT_DECLARE(Stats);
extern ECS_COMPONENT_DECLARE(PlayerController);
extern ECS_COMPONENT_DECLARE(Projectile);
extern ECS_COMPONENT_DECLARE(Collider);

extern ecs_entity_t BulletTag;

void ComponentsImport(ecs_world_t *world);

#endif
