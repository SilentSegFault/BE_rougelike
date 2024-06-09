#include "scene.h"
#include "../ecs/factories.h"
#include <stdlib.h>
#include "../logger/logger.h"
#include "../ecs/systems.h"
#include "../ecs/components.h"
#include "../utility/ut_math.h"

Scene CreateScene()
{
  Scene scene = {0};
  scene.isInitialized = FALSE;
  scene.entitiesToLoad = malloc(sizeof(SceneEntity));
  scene.entitiesToLoad = 0;

  return scene;
}

void AddEntityToScene(Scene *scene, SceneEntity entitiy)
{
  SceneEntity *newEntitiesToLoad = realloc(scene->entitiesToLoad, (scene->numOfEntitiesToLoad+1) * sizeof(SceneEntity));
  if(newEntitiesToLoad == NULL)
  {
    return;
  }

  scene->entitiesToLoad = newEntitiesToLoad;
  scene->entitiesToLoad[scene->numOfEntitiesToLoad] = entitiy;
  scene->numOfEntitiesToLoad++;
}

void InitScene(Scene *scene)
{
  if(scene->isInitialized)
    return;

  scene->world = EcsCreateWorld();
  RegisterComponents(scene->world);
  RegisterSystems(scene->world);

  for(int i = 0; i < scene->numOfEntitiesToLoad; i++)
  {
    CreateEntity(scene->world,
                 scene->entitiesToLoad[i].type,
                 scene->entitiesToLoad[i].position,
                 Deg2Rad(scene->entitiesToLoad[i].rotation),
                 scene->entitiesToLoad[i].parent);
  }
  scene->isInitialized = TRUE;
}

void DisposeScene(Scene *scene)
{
  EcsFreeWorld(scene->world);
  free(scene->entitiesToLoad);
  scene->entitiesToLoad = NULL;
  scene->numOfEntitiesToLoad = 0;
  scene->isInitialized = FALSE;
}
