#include "script_engine.h"
#include "lua54/lua.h"
#include "lua54/lualib.h"
#include "lua54/lauxlib.h"
#include "../logger/logger.h"
#include <stdio.h>
#include <windows.h>
#include <stdarg.h>
#include "api.h"

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

LuaEntity CreateLuaEntity(const char *entity, int id)
{
  LuaEntity ent = {0};
  ent.id = -1;

  lua_getglobal(L, "NewEntity");
  lua_getglobal(L, entity);
  lua_pushnumber(L, id);

  if(lua_pcall(L, 2, 1, 0) != 0)
  {
    LogTagError("EntityCreation", "Failed creating entity `%s` [id:%i]", entity, id);
    return ent;
  }

  //Size
  lua_getfield(L, -1, "size");

  if(!lua_istable(L, -1))
  {
    LogTagError("EntityCreation", "%s: size should be table, but is %s", entity, lua_typename(L, lua_type(L, -1)));
    return ent;
  }

  lua_getfield(L, -1, "width");
  lua_getfield(L, -2, "height");

  if(!lua_isnumber(L, -1))
  {
    LogTagError("EntityCreation", "%s: size.height should be number", entity);
    return ent;
  }

  if(!lua_isnumber(L, -2))
  {
    LogTagError("EntityCreation", "%s: size.width should be number", entity);
    return ent;
  }

  ent.size.height = lua_tonumber(L, -1);
  ent.size.width = lua_tonumber(L, -2);

  lua_pop(L, 3);

  //Render
  lua_getfield(L, -1, "render");
  if(!lua_istable(L, -1))
  {
    LogTagError("EntityCreation", "%s: render should be table", entity);
    return ent;
  }

  lua_getfield(L, -1, "sprite");
  if(!lua_isstring(L, -1))
  {
    LogTagError("EntityCreation", "%s: render.sprite should be string", entity);
    return ent;
  }

  ent.render.sprite = lua_tostring(L, -1);
  lua_pop(L, 1);

  lua_getfield(L, -1, "drawLayer");
  if(!lua_isnumber(L, -1))
  {
    LogTagError("EntityCreation", "%s: render.drawLayer should be number", entity);
    return ent;
  }

  ent.render.drawLayer = lua_tonumber(L, -1);
  lua_pop(L, 1 + 1);

  //Stats
  lua_getfield(L, -1, "stats");

  if(!lua_istable(L, -1))
  {
    LogTagError("EntityCreation", "%s: stats should be table but is %s", entity, luaL_typename(L, -1));
    return ent;
  }

  lua_getfield(L, -1, "health");
  lua_getfield(L, -2, "speed");

  if(!lua_isnumber(L, -1))
  {
    LogTagError("EntityCreation", "%s: stats.speed should be number", entity);
    return ent;
  }

  if(!lua_isnumber(L, -2))
  {
    LogTagError("EntityCreation", "%s: stats.health should be number", entity);
    return ent;
  }

  ent.stats.health = lua_tonumber(L, -2);
  ent.stats.speed = lua_tonumber(L, -1);

  lua_pop(L, 3);

  //CollisionShape
  lua_getfield(L, -1, "collisionShape");

  if(!lua_isstring(L, -1))
  {
    LogTagError("EntityCreation", "%s: collisionShape should be a string", entity);
    return ent;
  }

  ent.collisionShape = lua_tostring(L, -1);

  lua_pop(L, 1);

  lua_pop(L, 1);

  ent.id = id;
  return ent;
}

void DisposeScriptingEngine()
{
  lua_close(L);
}
