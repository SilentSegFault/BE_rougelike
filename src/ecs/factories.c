#include "factories.h"
#include "components.h"
#include "../scripting/script_engine.h"
#include "../logger/logger.h"
#include "ecs.h"

EcsID CreateEntity(EcsWorld *world, const char *entity, vec2 position, float rotation, const char *parent)
{
  EcsID ent = EcsCreateEntity(world);

  if(!EntityExists(entity))
  {
    LogWarning("entity `%s` doesn't exists!", entity);
    CreateLuaEntity(world, "Entity", ent);
  }
  else
  {
    CreateLuaEntity(world, entity, ent);
  }

  Transform *transform = NULL;
  if(!EcsHasComponent(world, ent, TransformComp))
  {
    EcsAddComponent(world, ent, TransformComp);
  }

  transform = EcsGetComponent(world, ent, TransformComp);

  transform->position[0] = position[0];
  transform->position[1] = position[1];
  transform->rotation = rotation;

  transform->scale[0] = 1;
  transform->scale[1] = 1;

  CallOnCreate(ent);
  return ent;
}
