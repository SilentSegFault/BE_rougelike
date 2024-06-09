#include "script_engine.h"
#include "lua54/lua.h"
#include "lua54/lualib.h"
#include "lua54/lauxlib.h"
#include "../logger/logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
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
  int ok = luaL_dofile(L, scriptPath) == LUA_OK;
  if(!ok)
    LogTagError("ScriptEngine", "Error running lua script %s: %s", scriptPath, lua_tostring(L, -1)); 
  return ok;
}

BOOL EntityExists(const char *entity)
{
  lua_getglobal(L, "Ecs");
  lua_getfield(L, -1, "IsEntity");
  lua_insert(L, -2);
  lua_getglobal(L, entity);

  if(lua_pcall(L, 2, 1, 0) != 0)
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

void GetLuaEntity(int id)
{
  lua_getglobal(L, "Ecs");
  lua_getfield(L, -1, "GetEntity");
  lua_insert(L, -2);
  lua_pushnumber(L, id);

  if(lua_pcall(L, 2, 1, 0) != 0)
  {
    LogTagError("ScriptEngine", "Error running lua function `Ecs:GetEntity`: %s", lua_tostring(L, -1)); 
    return;
  }
}

void CallOnCreate(int id)
{
  GetLuaEntity(id);
  lua_getfield(L, -1, "OnCreate");
  lua_insert(L, -2);

  if(lua_pcall(L, 1, 0, 0) != LUA_OK)
  {
    LogTagError("ScriptEngine", "Failed running OnCreate: %s", lua_tostring(L, -1));
  }
}

void CallOnStart(int id)
{
  GetLuaEntity(id);
  lua_getfield(L, -1, "OnStart");
  lua_insert(L, -2);

  if(lua_pcall(L, 1, 0, 0) != LUA_OK)
  {
    LogTagError("ScriptEngine", "Failed running OnStart: %s", lua_tostring(L, -1));
  }
}

void CallOnUpdate(int id, float deltaTime)
{
  GetLuaEntity(id);
  lua_getfield(L, -1, "OnUpdate");
  lua_insert(L, -2);
  lua_pushnumber(L, deltaTime);

  if(lua_pcall(L, 2, 0, 0) != LUA_OK)
  {
    LogTagError("ScriptEngine", "Failed running OnUpdate: %s", lua_tostring(L, -1));
  }
}

void CallOnCollision(int id1, int id2)
{
  GetLuaEntity(id1);
  lua_getfield(L, -1, "OnCollision");
  lua_insert(L, -2);
  GetLuaEntity(id2);

  if(lua_pcall(L, 2, 0, 0) != LUA_OK)
  {
    LogTagError("ScriptEngine", "Failed running OnCollision: %s", lua_tostring(L, -1));
  }
}
void CallOnDestroy(int id)
{
  GetLuaEntity(id);
  lua_getfield(L, -1, "OnDestroy");
  lua_insert(L, -2);

  if(lua_pcall(L, 1, 0, 0) != LUA_OK)
  {
    LogTagError("ScriptEngine", "Failed running CallOnDestroy: %s", lua_tostring(L, -1));
  }
}

void AddTransformComp(EcsWorld *world, EcsID ent)
{
  Transform *transform = EcsAddComponent(world, ent, TransformComp);
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

}

void AddSpriteRenderComp(EcsWorld *world, EcsID ent)
{
  SpriteRender *spriteRender = EcsAddComponent(world, ent, SpriteRenderComp);
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
}

void AddTilemapRenderComp(EcsWorld *world, EcsID ent)
{
  TilemapRender *tilemapRender = EcsAddComponent(world, ent, TilemapRenderComp);

  lua_getfield(L, -1, "tilemap");
  if(lua_isstring(L, -1))
  {
    tilemapRender->tilemap = GetTilemap(lua_tostring(L, -1));
  }
  else
  {
    tilemapRender->tilemap = GetTilemap("default");
    LogTagWarning("EntityCreation", "tilemapRender.tilemap is nil.");
  }
  lua_pop(L, 1);
}

void AddTextRenderComp(EcsWorld *world, EcsID ent)
{
  TextRender *textRender = EcsAddComponent(world, ent, TextRenderComp);

  lua_getfield(L, -1, "text");
  if(lua_isstring(L, -1))
  {
    textRender->text = lua_tostring(L, -1);
  }
  else
  {
    textRender->text = NULL;
    LogTagWarning("EntityCreation", "textRender.text is nil.");
  }
  lua_pop(L, 1);

  lua_getfield(L, -1, "font");
  if(lua_isstring(L, -1))
  {
    textRender->font = lua_tostring(L, -1);
  }
  else
  {
    textRender->font = "arial";
    LogTagWarning("EntityCreation", "textRender.font is nil.");
  }
  lua_pop(L, 1);

  lua_getfield(L, -1, "scale");
  if(lua_isnumber(L, -1))
  {
    textRender->scale = lua_tonumber(L, -1);
  }
  else
  {
    textRender->scale = 1;
    LogTagWarning("EntityCreation", "textRender.scale is nil.");
  }
  lua_pop(L, 1);

  lua_getfield(L, -1, "color");
  if(lua_istable(L, -1))
  {
    lua_getfield(L, -1, "r");
    lua_getfield(L, -2, "g");
    lua_getfield(L, -3, "b");

    if(lua_isnumber(L, -3))
    {
      textRender->color[0] = lua_tonumber(L, -3) / 255.0f;
    }
    else
    {
      textRender->color[0] = 1.0;
    LogTagWarning("EntityCreation", "textRender.color.r is nil.");
    }

    if(lua_isnumber(L, -2))
    {
      textRender->color[1] = lua_tonumber(L, -2) / 255.0f;
    }
    else
    {
      textRender->color[1] = 1.0;
    LogTagWarning("EntityCreation", "textRender.color.g is nil.");
    }

    if(lua_isnumber(L, -1))
    {
      textRender->color[2] = lua_tonumber(L, -1) / 255.0f;
    }
    else
    {
      textRender->color[2] = 1.0;
    LogTagWarning("EntityCreation", "textRender.color.b is nil.");
    }

    lua_pop(L, 3);
  }
  else
  {
    textRender->color[0] = 1.0;
    textRender->color[1] = 1.0;
    textRender->color[2] = 1.0;
    LogTagWarning("EntityCreation", "textRender.color is nil.");
  }
  lua_pop(L, 1);

  textRender->drawLayer = 0;
}

void AddAnimatorComp(EcsWorld *world, EcsID ent)
{
  Animator *animator = EcsAddComponent(world, ent, AnimatorComp);

  lua_getfield(L, -1, "animation");
  if(lua_isstring(L, -1))
  {
    animator->currentAnimation = GetAnimation(lua_tostring(L, -1));
  }
  else
  {
    animator->currentAnimation = GetAnimation("default");
    LogTagWarning("EntityCreation", "animator.animation is nil.");
  }
  lua_pop(L, 1);

  lua_getfield(L, -1, "drawLayer");
  if(lua_isnumber(L, -1))
  {
    animator->drawLayer = lua_tonumber(L, -1);
  }
  else
  {
    animator->drawLayer = 0;
    LogTagWarning("EntityCreation", "animator.drawLayer is nil.");
  }
  lua_pop(L, 1);

  animator->flip = FALSE;
}

void AddColliderComp(EcsWorld *world, EcsID ent)
{
  Collider *collider = EcsAddComponent(world, ent, ColliderComp);
  lua_getfield(L, -1, "width");
  lua_getfield(L, -2, "height");

  if(lua_isnumber(L, -1))
  {
    collider->height = lua_tonumber(L, -1);
  }
  else
  {
    LogTagWarning("EntityCreation", "collider.height is nil.");
    collider->height = 1;
  }

  if(lua_isnumber(L, -2))
  {
    collider->width = lua_tonumber(L, -2);
  }
  else
  {
    LogTagWarning("EntityCreation", "collider.width is nil.");
    collider->width = 1;
  }

  lua_pop(L, 2);

  collider->collisionLayer = 0;
}

void AddStatsComp(EcsWorld *world, EcsID ent)
{
  Stats *stats = EcsAddComponent(world, ent, StatsComp);
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

void CreateLuaEntity(EcsWorld *world, const char *entity, int id)
{
  lua_getglobal(L, "Ecs");
  lua_getfield(L, -1, "AddEntity");
  lua_insert(L, -2);

  lua_getglobal(L, entity);
  lua_getfield(L, -1, "New");
  lua_insert(L, -2);
  lua_pushnil(L);
  lua_pushnumber(L, id);

  if(lua_pcall(L, 3, 1, 0) != LUA_OK)
  {
    LogTagError("EntityCreation", "Failed creating entity `%s` [id:%i]", entity, id);
    return;
  }

  lua_getfield(L, -1, "components");

  //Transform
  if(GetComponentIfExists("transform"))
  {
    AddTransformComp(world, id);
    lua_pop(L, 1);
  }

  //SpriteRender
  if(GetComponentIfExists("spriteRender"))
  {
    AddSpriteRenderComp(world, id);
    lua_pop(L, 1);
  }

  //TilemapRender
  if(GetComponentIfExists("tilemapRender"))
  {
    AddTilemapRenderComp(world, id);
    lua_pop(L, 1);
  }
  
  //TextRender
  if(GetComponentIfExists("textRender"))
  {
    AddTextRenderComp(world, id);
    lua_pop(L, 1);
  }

  //Stats
  if(GetComponentIfExists("stats"))
  {
    AddStatsComp(world, id);
    lua_pop(L, 1);
  }

  //Collider
  if(GetComponentIfExists("collider"))
  {
    AddColliderComp(world, id);
    lua_pop(L, 1);
  }

  //Animator
  if(GetComponentIfExists("animator"))
  {
    AddAnimatorComp(world, id);
    lua_pop(L, 1);
  }

  //Required tags
  EcsAddComponent(world, id, NewTag);
  EcsAddComponent(world, id, UpdateTag);

  lua_pop(L, 1);

  if(lua_pcall(L, 2, 0, 0) != LUA_OK)
  {
    LogTagError("EntityCreation", "Failed adding entity `%s` [id:%i]", entity, id);
    return;
  }
}

void CallRemoveEntity(int id)
{
  lua_getglobal(L, "Ecs");
  lua_getfield(L, -1, "RemoveEntity");
  lua_insert(L, -2);
  lua_pushnumber(L, id);

  if(lua_pcall(L, 2, 0, 0) != LUA_OK)
  {
    LogTagError("ScriptEngine", "Failed running RemoveEntity: %s", lua_tostring(L, -1));
  }
}

void LoadLuaScene(const char *name)
{
  lua_getglobal(L, "Ecs");
  lua_getfield(L, -1, "LoadScene");
  lua_insert(L, -2);
  lua_pushstring(L, name);

  if(lua_pcall(L, 2, 0, 0) != LUA_OK)
  {
    LogTagError("ScriptEngine", "Failed running LoadScene: %s", lua_tostring(L, -1));
  }
}

void DisposeScriptingEngine()
{
  lua_close(L);
}
