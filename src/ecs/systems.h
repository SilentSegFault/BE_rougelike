#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "flecs/flecs.h"

void SpriteRenderSystem(ecs_iter_t *it);

extern ECS_SYSTEM_DECLARE(SpriteRenderSystem);

void SystemsModuleImport(ecs_world_t *world);

#endif
