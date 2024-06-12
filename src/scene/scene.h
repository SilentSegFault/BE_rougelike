#ifndef SCENE_H
#define SCENE_H

#include "cglm/types.h"
#include "../ecs/ecs.h"
#include <windows.h>

typedef struct
{
  const char *type;
  const char *name;
  vec2 position;
  float rotation;
  const char *parent;
} SceneEntity;

typedef struct
{
  EcsWorld *world;
  BOOL isInitialized;
  long numOfEntitiesToLoad;
  SceneEntity *entitiesToLoad;

} Scene;

Scene CreateScene();
void AddEntityToScene(Scene *scene, SceneEntity entitiy);
void InitScene(Scene *scene);
void DisposeScene(Scene *scene);

#endif
