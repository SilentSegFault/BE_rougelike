#include "api.h"
#include "lua54/lauxlib.h"
#include "lua54/lua.h"

#include "../logger/logger.h"
#include "../ecs/components.h"
#include "../game/game.h"
#include "../window/win32_helper.h"
#include <string.h>

void RegisterFunction(lua_State *L, const char *name, lua_CFunction func)
{
  lua_pushcfunction(L, func);
  lua_setglobal(L, name);
}

int api_LogTrace(lua_State *L)
{
  const char *msg = luaL_checkstring(L, 1);
  if(msg != NULL)
    LogTagTrace("LuaApi", msg);

  return 0;
}

int api_LogDebug(lua_State *L)
{
  const char *msg = luaL_checkstring(L, 1);
  if(msg != NULL)
    LogTagDebug("LuaApi", msg);

  return 0;
}

int api_LogInfo(lua_State *L)
{
  const char *msg = luaL_checkstring(L, 1);
  if(msg != NULL)
    LogTagInfo("LuaApi", msg);

  return 0;
}

int api_LogWarning(lua_State *L)
{
  const char *msg = luaL_checkstring(L, 1);
  if(msg != NULL)
    LogTagWarning("LuaApi", msg);

  return 0;
}

int api_LogError(lua_State *L)
{
  const char *msg = luaL_checkstring(L, 1);
  if(msg != NULL)
    LogTagError("LuaApi", msg);

  return 0;
}

int api_LogFatal(lua_State *L)
{
  const char *msg = luaL_checkstring(L, 1);
  if(msg != NULL)
    LogTagFatal("LuaApi", msg);

  return 0;
}

int api_MoveEntity(lua_State *L)
{
  float dx = luaL_checknumber(L, 2);
  float dy = luaL_checknumber(L, 3);
  lua_getfield(L, 1, "id");
  int id = luaL_checknumber(L, -1);
  lua_pop(L, 1);

  Transform *transform = ecs_get_mut_id(GetCurrentScene()->world, id, ecs_id(Transform));
  transform->position[0] += dx;
  transform->position[1] += dy;

  return 0;
}

int api_FlipLeft(lua_State *L)
{
  lua_getfield(L, 1, "id");
  int id = luaL_checknumber(L, -1);
  lua_pop(L, 1);

  SpriteRender *spriteRender = ecs_get_mut_id(GetCurrentScene()->world, id, ecs_id(SpriteRender));

  if(!spriteRender->flipX)
    spriteRender->flipX = TRUE;

  return 0;
}

int api_FlipRight(lua_State *L)
{
  lua_getfield(L, 1, "id");
  int id = luaL_checknumber(L, -1);
  lua_pop(L, 1);

  SpriteRender *spriteRender = ecs_get_mut_id(GetCurrentScene()->world, id, ecs_id(SpriteRender));

  if(spriteRender->flipX)
    spriteRender->flipX = FALSE;

  return 0;
}

Key StrToKey(const char *str)
{
  if(strcmp(str, "key_w") == 0)
  {
    return KEY_W;
  }
  else if(strcmp(str, "key_a") == 0)
  {
    return KEY_A;
  }
  else if(strcmp(str, "key_s") == 0)
  {
    return KEY_S;
  }
  else if(strcmp(str, "key_d") == 0)
  {
    return KEY_D;
  }
  else if(strcmp(str, "mouse_left") == 0)
  {
    return KEY_MOUSELEFT;
  }
  else if(strcmp(str, "key_p") == 0)
  {
    return KEY_P;
  }

  return KEY_NONE;
}

int api_KeyPressed(lua_State *L)
{
  const char *keyName = luaL_checkstring(L, 1);

  if(keyName == NULL)
  {
    LogTagWarning("LuaApi", "Invalid argument type in `KeyPressed`");
    lua_pushboolean(L, FALSE);
    return 1;
  }

  Key key = StrToKey(keyName);

  BOOL keyPressed = KeyPressed(key);
  lua_pushboolean(L, keyPressed);
  return 1;
}

int api_KeyDown(lua_State *L)
{
  const char *keyName = luaL_checkstring(L, 1);

  if(keyName == NULL)
  {
    LogTagWarning("LuaApi", "Invalid argument type in `KeyPressed`");
    lua_pushboolean(L, FALSE);
    return 1;
  }

  Key key = StrToKey(keyName);

  BOOL keyDown = KeyDown(key);
  lua_pushboolean(L, keyDown);
  return 1;
}

void RegisterApiFunctions(lua_State *L)
{
  //Logging
  RegisterFunction(L, "LogTrace", api_LogTrace);
  RegisterFunction(L, "LogDebug", api_LogDebug);
  RegisterFunction(L, "LogInfo", api_LogInfo);
  RegisterFunction(L, "LogWarning", api_LogWarning);
  RegisterFunction(L, "LogError", api_LogError);
  RegisterFunction(L, "LogFatal", api_LogFatal);

  //Transfoms
  RegisterFunction(L, "MoveEntity", api_MoveEntity);
  RegisterFunction(L, "FlipLeft", api_FlipLeft);
  RegisterFunction(L, "FlipRight", api_FlipRight);

  //Input
  RegisterFunction(L, "KeyPressed", api_KeyPressed);
  RegisterFunction(L, "KeyDown", api_KeyDown);
}
