#ifndef SCRIPTING_ENGINE_H
#define SCRIPTING_ENGINE_H

#include <windows.h>
#include "../ecs/ecs.h"

void InitScriptingEngine();
int RunScript(const char *scriptPath);

BOOL EntityExists(const char *entity);
void GetLuaEntity(int id);
void CreateLuaEntity(EcsWorld *world, const char *entity, int id);
void CallOnStart(int id);
void CallOnCreate(int id);
void CallOnUpdate(int id, float deltaTime);
void CallOnCollision(int id1, int id2);
void CallOnDestroy(int id);
void CallAddEntity(int id);
void CallRemoveEntity(int id);
void LoadLuaScene(const char *name);

void DisposeScriptingEngine();

#endif
