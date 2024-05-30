#include "factories.h"
#include "components.h"
#include "../scripting/script_engine.h"
#include "../logger/logger.h"
#include "../resource_management/assets_library.h"

ecs_entity_t CreateEntity(ecs_world_t *world, const char *entity, const char *name, vec2 position, float rotation, const char *parent)
{
  ecs_entity_t ent = ecs_new_id(world);
  if(name != NULL)
  {
    ecs_set_name(world, ent, name);
  }

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
  if(!ecs_has_id(world, ent, ecs_id(Transform)))
  {
    ecs_add_id(world, ent, ecs_id(Transform));
  }

  transform = ecs_get_mut_id(world, ent, ecs_id(Transform));

  transform->position[0] = position[0];
  transform->position[1] = position[1];
  transform->rotation = rotation;

  if(parent != NULL)
  {
    ecs_id_t parentId = ecs_lookup(world, parent);
    if(parentId == 0)
    {
      LogWarning("Entity with name `%s` doesn't exists", parent);
    }
    else
    {
      transform->parent = parentId;
    }
  }

  CallOnCreate(ent);

  return ent;
}
