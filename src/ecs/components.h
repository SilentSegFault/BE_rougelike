#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "flecs/flecs.h"
#include "cglm/types.h"
#include "../sprite/sprite.h"
#include "../tilemap/tilemap.h"

typedef struct Transform Transform;
struct Transform
{
  vec2 position;
  vec2 size;
  vec2 scale;
  float rotation;

  int parent;
};

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
  char *text;
  char *font;
  float scale;
  vec3 color;
  int drawLayer;
} TextRender;

typedef struct
{
  float health;
  float speed;
} Stats;

typedef struct
{
  float width, height;
  float offsetX, offsetY;
} Collider;

extern ecs_entity_t PlayerTag;
extern ecs_entity_t EnemyTag;
extern ecs_entity_t ProjectileTag;
extern ecs_entity_t ItemTag;

extern ECS_COMPONENT_DECLARE(Transform);
extern ECS_COMPONENT_DECLARE(SpriteRender);
extern ECS_COMPONENT_DECLARE(TilemapRender);
extern ECS_COMPONENT_DECLARE(TextRender);
extern ECS_COMPONENT_DECLARE(Stats);
extern ECS_COMPONENT_DECLARE(Collider);

void ComponentsModuleImport(ecs_world_t *world);

#endif
