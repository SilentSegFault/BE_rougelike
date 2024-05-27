#include "factories.h"
#include "components.h"
#include "../scripting/script_engine.h"
#include "../logger/logger.h"
#include "../resource_management/assets_library.h"

void CreateEntity(ecs_world_t *world, const char *entity, vec2 position, float rotation)
{
  ecs_entity_t ent = ecs_new_id(world);
  LuaEntity luaEnt;

  if(!EntityExists(entity))
  {
    LogWarning("entity `%s` doesn't exists!", entity);
    luaEnt = CreateLuaEntity("Entity", ent);
  }
  else
  {
    luaEnt = CreateLuaEntity(entity, ent);
  }

  ecs_set(world, ent, Transform, {.rotation = rotation,
                                  .position = {position[0], position[1]},
                                  .size = {luaEnt.size.width, luaEnt.size.height}});
  ecs_set(world, ent, SpriteRender, {.drawLayer = luaEnt.render.drawLayer,
                                     .sprite = GetSprite(luaEnt.render.sprite),
                                     .visible = TRUE,
                                     .flipX = FALSE,
                                     .flipY = FALSE});

  CallOnCreate(ent);
}
