#include "script_engine.h"
#include "lua54/lua.h"
#include "lua54/lualib.h"
#include "lua54/lauxlib.h"
#include "../logger/logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdarg.h>
#include "api.h"
#include "../ecs/components.h"
#include "../resource_management/assets_library.h"

static lua_State *L;

void InitScriptingEngine()
{
  L = luaL_newstate();
  luaL_openlibs(L);

  RegisterApiFunctions(L);
}

int RunScript(const char *scriptPath)
{
  return luaL_dofile(L, scriptPath) == LUA_OK;
}

void RunScriptsFromDirectory(const char *scriptsDirPath)
{
  char path[MAX_PATH];
  sprintf_s(path, MAX_PATH, "%s/*.lua", scriptsDirPath);

  WIN32_FIND_DATA data;
  HANDLE hFind = FindFirstFile(path, &data);

  if(hFind != INVALID_HANDLE_VALUE)
  {

    do
    {
      char scriptFilePath[MAX_PATH];
      sprintf_s(scriptFilePath, MAX_PATH, "%s/%s", scriptsDirPath, data.cFileName);
      if(RunScript(scriptFilePath))
      {
        LogTagInfo("ScriptEngine", "Succesfully ran script `%s`", data.cFileName);
      }
      else
    {
        LogTagError("ScriptEngine", "Failed running script `%s`: \"%s\"", data.cFileName, lua_tostring(L, -1));
      }

    } while(FindNextFile(hFind, &data));

    FindClose(hFind);
  }
}

void CallOnCreate(int id)
{
  lua_getglobal(L, "CallOnCreate");
  lua_pushnumber(L, id);

  if(lua_pcall(L, 1, 0, 0) != LUA_OK)
  {
    LogTagError("ScriptEngine", "Failed running OnCreate: %s", id, lua_tostring(L, -1));
  }
}

void CallOnUpdate(int id, float deltaTime)
{
  lua_getglobal(L, "CallOnUpdate");
  lua_pushnumber(L, id);
  lua_pushnumber(L, deltaTime);

  if(lua_pcall(L, 1, 0, 0) != LUA_OK)
  {
    LogTagError("ScriptEngine", "Failed running OnUpdate: %s", id, lua_tostring(L, -1));
  }

}

void CallOnDestroy(int id)
{
  lua_getglobal(L, "CallOnDestroy");
  lua_pushnumber(L, id);

  if(lua_pcall(L, 1, 0, 0) != LUA_OK)
  {
    LogTagError("ScriptEngine", "Failed running CallOnDestroy: %s", id, lua_tostring(L, -1));
  }
}

void UpdateEntities(float deltaTime)
{
  lua_getglobal(L, "UpdateEntities");
  lua_pushnumber(L, deltaTime);

  if(lua_pcall(L, 1, 0, 0) != LUA_OK)
  {
    LogTagError("ScriptEngine", "Failed running UpdateEntities: %s", lua_tostring(L, -1));
  }
}

BOOL EntityExists(const char *entity)
{
  lua_getglobal(L, "IsEntity");
  lua_getglobal(L, entity);

  if(lua_pcall(L, 1, 1, 0) != 0)
  {
    LogTagError("ScriptEngine", "Error running lua function `IsEntity`: %s", lua_tostring(L, -1)); 
    return FALSE;
  }

  if(!lua_isboolean(L, -1))
  {
    LogTagError("ScriptEngine", "`IsEntity` must return boolean!"); 
    return FALSE;
  }

  BOOL exists = lua_toboolean(L, -1);
  lua_pop(L, 1);
  return exists;
}

void AddTransformComp(ecs_world_t *world, ecs_entity_t ent)
{
  Transform *transform = calloc(1, sizeof(Transform));
  lua_getfield(L, -1, "size");

  if(lua_istable(L, -1))
  {
    lua_getfield(L, -1, "width");
    lua_getfield(L, -2, "height");

    if(!lua_isnumber(L, -1))
    {
      LogTagError("EntityCreation", "Transform.size.height should be a number");
      transform->size[1] = 1;
    }
    else
    {
      transform->size[1] = lua_tonumber(L, -1);
    }

    if(!lua_isnumber(L, -2))
    {
      LogTagError("EntityCreation", "Transform.size.width should be a number");
      transform->size[0] = 1;
    }
    else
    {
      transform->size[0] = lua_tonumber(L, -2);
    }
    lua_pop(L, 3);
  }
  else
  {
    LogTagWarning("EntityCreation", "transform.size is nil.");
    transform->size[1] = 1;
    transform->size[0] = 1;
    lua_pop(L, 1);
  }

  ecs_set_id(world, ent, ecs_id(Transform), sizeof(Transform), transform);
}

void AddSpriteRenderComp(ecs_world_t *world, ecs_entity_t ent)
{
  SpriteRender *spriteRender = calloc(1, sizeof(SpriteRender));
  lua_getfield(L, -1, "sprite");
  if(lua_isstring(L, -1))
  {
    spriteRender->sprite = GetSprite(lua_tostring(L, -1));
  }
  else
  {
    LogTagWarning("EntityCreation", "spriteRender.sprite is nil.");
    spriteRender->sprite = GetSprite("default");
  }
  lua_pop(L, 1);

  lua_getfield(L, -1, "drawLayer");
  if(lua_isnumber(L, -1))
  {
    spriteRender->drawLayer = lua_tonumber(L, -1);
  }
  else
  {
    LogTagWarning("EntityCreation", "spriteRender.drawLayer is nil.");
    spriteRender->drawLayer = 0;
  }
  lua_pop(L, 1);

  spriteRender->visible = TRUE;

  ecs_set_id(world, ent, ecs_id(SpriteRender), sizeof(SpriteRender), spriteRender);
}

void AddTilemapRenderComp(ecs_world_t *world, ecs_entity_t ent)
{
}

void AddTextRenderComp(ecs_world_t *world, ecs_entity_t ent)
{
}

void AddColliderComp(ecs_world_t *world, ecs_entity_t ent)
{
}

void AddStatsComp(ecs_world_t *world, ecs_entity_t ent)
{
  Stats *stats = calloc(1, sizeof(Stats));
  lua_getfield(L, -1, "health");
  lua_getfield(L, -2, "speed");

  if(lua_isnumber(L, -1))
  {
    stats->speed = lua_tonumber(L, -1);
  }
  else
  {
    LogTagWarning("EntityCreation", "stats.speed is nil.");
    stats->speed = 0;
  }

  if(lua_isnumber(L, -2))
  {
    stats->health = lua_tonumber(L, -2);
  }
  else
  {
    LogTagWarning("EntityCreation", "stats.health is nil.");
    stats->health = 0;
  }

  lua_pop(L, 2);

  ecs_set_id(world, ent, ecs_id(Stats), sizeof(Stats), stats);
}

int GetComponentIfExists(const char *comp)
{
  lua_getfield(L, -1, comp);
  if(lua_type(L, -1) != LUA_TTABLE)
  {
    lua_pop(L, 1);
    return 0;
  }
  return 1;
}

void CreateLuaEntity(ecs_world_t *world, const char *entity, ecs_entity_t id)
{
  lua_getglobal(L, "NewEntity");
  lua_getglobal(L, entity);
  lua_pushnumber(L, id);

  if(lua_pcall(L, 2, 1, 0) != 0)
  {
    LogTagError("EntityCreation", "Failed creating entity `%s` [id:%i]", entity, id);
    return;
  }

  //Transform
  if(GetComponentIfExists("transform"))
  {
    LogDebug("Adding transform");
    AddTransformComp(world, id);
    lua_pop(L, 1);
  }

  //SpriteRender
  if(GetComponentIfExists("spriteRender"))
  {
    LogDebug("Adding spriteRender");
    AddSpriteRenderComp(world, id);
    lua_pop(L, 1);
  }

  //Stats
  if(GetComponentIfExists("stats"))
  {
    LogDebug("Adding stats");
    AddStatsComp(world, id);
    lua_pop(L, 1);
  }

  //Pop entity
  lua_pop(L, 1);
}

void DisposeScriptingEngine()
{
  lua_close(L);
}
