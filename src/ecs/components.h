#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "ecs.h"
#include "cglm/types.h"
#include <windows.h>
#include "../sprite/sprite.h"
#include "../tilemap/tilemap.h"
#include "../animation/animation.h"

typedef struct
{
  vec2 position;
  vec2 size;
  vec2 scale;
  float rotation;

  EcsID parent;
  long numOfChildren;
  EcsID *children;
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
  const char *text;
  const char *font;
  float scale;
  vec3 color;
  int drawLayer;
} TextRender;

typedef struct
{
  Animation *currentAnimation;
  int currentFrame;
  int frameCounter;
  BOOL flip;
  int drawLayer;
} Animator;

typedef struct
{
  float health;
  float speed;
} Stats;

typedef struct
{
  int collisionLayer;
  float width, height;
  float offsetX, offsetY;
} Collider;

typedef struct
{
  const char *name;
  const char *type;
} GameObject;

extern EcsID TransformComp;
extern EcsID SpriteRenderComp;
extern EcsID TilemapRenderComp;
extern EcsID TextRenderComp;
extern EcsID AnimatorComp;
extern EcsID StatsComp;
extern EcsID ColliderComp;
extern EcsID GameObjectComp;

extern EcsID NewTag;
extern EcsID UpdateTag;
extern EcsID DestroyTag;

void RegisterComponents(EcsWorld *world);

#endif
