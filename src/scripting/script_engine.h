#ifndef SCRIPTING_ENGINE_H
#define SCRIPTING_ENGINE_H

#include <windows.h>
#include "flecs/flecs.h"

void InitScriptingEngine();
int RunScript(const char *scriptPath);
void RunScriptsFromDirectory(const char *scriptsDirPath);

BOOL EntityExists(const char *entity);
void CreateLuaEntity(ecs_world_t *world, const char *entity, ecs_entity_t id);
void CallOnCreate(int id);
void CallOnUpdate(int id, float deltaTime);
void CallOnDestroy(int id);
void UpdateEntities(float deltaTime);

void DisposeScriptingEngine();

#endif
