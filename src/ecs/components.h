#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "flecs/flecs.h"
#include "cglm/types.h"
#include "../sprite/sprite.h"
#include "../tilemap/tilemap.h"

typedef struct
{
  vec2 position;
  vec2 size;
  float rotation;
} Transform;

typedef struct
{
  Sprite *sprite;
  BOOL visible;
  BOOL flipX;
  BOOL flipY;
  int drawLayer;
} SpriteRender;

typedef struct
{
  Tilemap *tilemap;
} TilemapRender;

typedef struct
{
  float health;
  float speed;
} Stats;

typedef struct
{
  const char *shape;
} Collider;

extern ECS_COMPONENT_DECLARE(Transform);
extern ECS_COMPONENT_DECLARE(SpriteRender);
extern ECS_COMPONENT_DECLARE(TilemapRender);
extern ECS_COMPONENT_DECLARE(Stats);
extern ECS_COMPONENT_DECLARE(Collider);

void ComponentsModuleImport(ecs_world_t *world);

#endif
