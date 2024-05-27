#ifndef SCRIPTING_ENGINE_H
#define SCRIPTING_ENGINE_H

#include <windows.h>

typedef struct
{
  int id;
  struct {float width; float height;} size;
  struct {const char *sprite; int drawLayer;} render;
  struct {float health; float speed;} stats;
  const char *collisionShape;
} LuaEntity;

void InitScriptingEngine();
int RunScript(const char *scriptPath);
void RunScriptsFromDirectory(const char *scriptsDirPath);

BOOL EntityExists(const char *entity);
LuaEntity CreateLuaEntity(const char *entity, int id);
void CallOnCreate(int id);
void CallOnUpdate(int id, float deltaTime);
void CallOnDestroy(int id);
void UpdateEntities(float deltaTime);

void DisposeScriptingEngine();

#endif
