#include "api.h"
#include "lua54/lauxlib.h"
#include "lua54/lua.h"

#include "../logger/logger.h"
#include "../ecs/components.h"
#include "../ecs/factories.h"
#include "../game/game.h"
#include "../window/win32_helper.h"
#include "cglm/cglm.h"
#include <string.h>
#include "../utility/ut_math.h"

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

int api_SetEntityPos(lua_State *L)
{
  float x = luaL_checknumber(L, 2);
  float y = luaL_checknumber(L, 3);
  lua_getfield(L, 1, "id");
  int id = luaL_checknumber(L, -1);
  lua_pop(L, 1);

  Transform *transform = ecs_get_mut_id(GetCurrentScene()->world, id, ecs_id(Transform));
  transform->position[0] = x;
  transform->position[1] = y;

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

int api_GetMousePos(lua_State *L)
{
  lua_pushnumber(L, mouseX);
  lua_pushnumber(L, mouseY);

  return 2;
}

int api_SpawnEntity(lua_State *L)
{
  const char *entity = luaL_checkstring(L, 1);
  float x = luaL_checknumber(L, 2);
  float y = luaL_checknumber(L, 3);
  float rotation = luaL_checknumber(L, 4);

  if(entity == NULL)
  {
    LogTagWarning("LuaApi", "Invalid argument type in `SpawnEntity`");
    return 0;
  }

  int e = CreateEntity(GetCurrentScene()->world, entity, NULL, (vec2) {x, y}, rotation, NULL);
  lua_pushnumber(L, e);
  return 1;
}

int api_SpawnNamedEntity(lua_State *L)
{
  const char *entity = luaL_checkstring(L, 1);
  const char *name = luaL_checkstring(L, 2);
  float x = luaL_checknumber(L, 3);
  float y = luaL_checknumber(L, 4);
  float rotation = luaL_checknumber(L, 5);

  if(entity == NULL)
  {
    LogTagWarning("LuaApi", "Invalid argument type in `SpawnNamedEntity`");
    return 0;
  }

  if(name == NULL)
  {
    LogTagWarning("LuaApi", "Invalid argument type in `SpawnNamedEntity`");
    return 0;
  }

  int e = CreateEntity(GetCurrentScene()->world, entity, name, (vec2) {x, y}, rotation, NULL);
  lua_pushnumber(L, e);
  return 1;
}

int api_EntityLookAt(lua_State *L)
{
  float x = luaL_checknumber(L, 2);
  float y = luaL_checknumber(L, 3);
  lua_getfield(L, 1, "id");
  int id = luaL_checknumber(L, -1);
  lua_pop(L, 1);

  Transform *transform = ecs_get_mut_id(GetCurrentScene()->world, id, ecs_id(Transform));
  vec2 dir;
  glm_vec2_sub((vec2) {x, y}, transform->position, dir);

  float rotation = GetAngleBetweenVectors((vec2) {1,0}, dir);
  transform->rotation = rotation;

  return 0;
}

int api_GetEntityPos(lua_State *L)
{
  lua_getfield(L, 1, "id");
  int id = luaL_checknumber(L, -1);
  lua_pop(L, 1);

  Transform *transform = ecs_get_mut_id(GetCurrentScene()->world, id, ecs_id(Transform));
  lua_pushnumber(L, transform->position[0]);
  lua_pushnumber(L, transform->position[1]);

  return 2;
}

int api_GetDirection(lua_State *L)
{
  float x1 = luaL_checknumber(L, 1);
  float y1 = luaL_checknumber(L, 2);
  float x2 = luaL_checknumber(L, 3);
  float y2 = luaL_checknumber(L, 4);

  vec2 dir;
  glm_vec2_sub((vec2) {x2, y2}, (vec2) {x1, y1}, dir);
  glm_vec2_normalize(dir);

  lua_pushnumber(L, dir[0]);
  lua_pushnumber(L, dir[1]);

  return 2;
}

int api_GetEntityRotation(lua_State *L)
{
  lua_getfield(L, 1, "id");
  int id = luaL_checknumber(L, -1);
  lua_pop(L, 1);

  Transform *transform = ecs_get_mut_id(GetCurrentScene()->world, id, ecs_id(Transform));
  lua_pushnumber(L, transform->rotation);

  return 1;
}

int api_GetEntityByName(lua_State *L)
{
  const char *name = luaL_checkstring(L, 1);

  if(name == NULL)
  {
    LogTagWarning("LuaApi", "Invalid argument in `GetEntityByName`");
    return 0;
  }

  int id = ecs_lookup(GetCurrentScene()->world, name);
  if(id == 0)
  {
    LogTagWarning("LuaApi", "Trying to get entity with name `%s` but it doesn't exists", name);
    return 0;
  }

  lua_pushnumber(L, id);
  return 1;
}

int api_SetEntityParent(lua_State *L)
{
  lua_getfield(L, 1, "id");
  int id = luaL_checknumber(L, -1);
  lua_pop(L, 1);

  int parentId = luaL_checknumber(L, 2);
  
  Transform *transform = ecs_get_mut_id(GetCurrentScene()->world, id, ecs_id(Transform));
  transform->parent = parentId;

  return 0;
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
  RegisterFunction(L, "SetEntityPos", api_SetEntityPos);
  RegisterFunction(L, "FlipLeft", api_FlipLeft);
  RegisterFunction(L, "FlipRight", api_FlipRight);
  RegisterFunction(L, "EntityLookAt", api_EntityLookAt);

  //???
  RegisterFunction(L, "GetEntityPos", api_GetEntityPos);
  RegisterFunction(L, "GetDirection", api_GetDirection);
  RegisterFunction(L, "GetEntityRotation", api_GetEntityRotation);

  //Input
  RegisterFunction(L, "KeyPressed", api_KeyPressed);
  RegisterFunction(L, "KeyDown", api_KeyDown);
  RegisterFunction(L, "GetMousePos", api_GetMousePos);

  //Management
  RegisterFunction(L, "SpawnEntity", api_SpawnEntity);
  RegisterFunction(L, "SpawnNamedEntity", api_SpawnNamedEntity);
  RegisterFunction(L, "GetEntityByName", api_GetEntityByName);
  RegisterFunction(L, "SetEntityParent", api_SetEntityParent);
}
