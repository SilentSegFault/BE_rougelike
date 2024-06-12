#include "scene_management.h"
#include "cJSON/cJSON.h"
#include "../logger/logger.h"
#include <stdlib.h>
#include <string.h>

const char *pathToScenesDir;

void SetScenesDirPath(const char *path)
{
  pathToScenesDir = path;
}

SceneEntity LoadSceneEntity(cJSON *entity)
{
  SceneEntity loadedEntity = {0};
  cJSON *name = cJSON_GetObjectItemCaseSensitive(entity, "name");
  cJSON *type = cJSON_GetObjectItemCaseSensitive(entity, "type");
  cJSON *position = cJSON_GetObjectItemCaseSensitive(entity, "position");
  cJSON *rotation = cJSON_GetObjectItemCaseSensitive(entity, "rotation");
  cJSON *parent = cJSON_GetObjectItemCaseSensitive(entity, "parent");

  if(cJSON_IsString(name))
  {
    char *nameBuf = malloc(sizeof(char) * strlen(name->valuestring));
    strcpy(nameBuf, name->valuestring);
    loadedEntity.name = nameBuf;
  }
  else
  {
    loadedEntity.name = NULL;
  }

  if(cJSON_IsString(type))
  {
    char *typeBuf = malloc(sizeof(char) * strlen(type->valuestring));
    strcpy(typeBuf, type->valuestring);
    loadedEntity.type = typeBuf;
  }
  else
  {
    LogTagWarning("SceneLoading", "Entity type should be a string!");
    loadedEntity.type = "Entity";
  }

  if(cJSON_IsNumber(rotation))
  {
    loadedEntity.rotation = rotation->valuedouble;
  }
  else
  {
    LogTagWarning("SceneLoading", "Entity rotation should be a number!");
    loadedEntity.rotation = 0;
  }

  if(cJSON_IsObject(position))
  {
    cJSON *posX = cJSON_GetObjectItemCaseSensitive(position, "x");
    cJSON *posY = cJSON_GetObjectItemCaseSensitive(position, "y");

    if(cJSON_IsNumber(posX))
    {
      loadedEntity.position[0] = posX->valuedouble;
    }
    else
    {
      LogTagWarning("SceneLoading", "Entity position.x should be a number!");
      loadedEntity.position[0] = 0;
    }

    if(cJSON_IsNumber(posY))
    {
      loadedEntity.position[1] = posY->valuedouble;
    }
    else
    {
      LogTagWarning("SceneLoading", "Entity position.y should be a number!");
      loadedEntity.position[1] = 0;
    }
  }
  else
  {
    LogTagWarning("SceneLoading", "Entity position should be an object!");
    loadedEntity.position[0] = 0;
    loadedEntity.position[1] = 0;
  }

  if(cJSON_IsString(parent))
  {
    char *parentBuf = malloc(sizeof(char) * strlen(parent->valuestring));
    strcpy(parentBuf, parent->valuestring);
    loadedEntity.parent = parentBuf;
  }
  else
  {
    loadedEntity.parent = NULL;
  }

  return loadedEntity;
}

int LoadSceneFromJson(cJSON *scene, Scene *loadedScene)
{
  cJSON *entities = cJSON_GetObjectItemCaseSensitive(scene, "entities");

  if(!cJSON_IsArray(entities))
  {
    LogTagError("SceneLoading", "Error loading scene! `entities` should be an array!");
    return 0;
  }

  *loadedScene = CreateScene();

  cJSON *entity = NULL;
  cJSON_ArrayForEach(entity, entities)
  {
    SceneEntity loadedEnt = LoadSceneEntity(entity);
    AddEntityToScene(loadedScene, loadedEnt);
  }

  return 1;
}


