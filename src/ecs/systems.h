#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "flecs/flecs.h"

void SpriteRenderSystem(ecs_iter_t *it);
void TilemapRenderSystem(ecs_iter_t *it);
void TextRenderSystem(ecs_iter_t *it);

extern ECS_SYSTEM_DECLARE(SpriteRenderSystem);
extern ECS_SYSTEM_DECLARE(TilemapRenderSystem);
extern ECS_SYSTEM_DECLARE(TextRenderSystem);

void SystemsModuleImport(ecs_world_t *world);

#endif
