#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "components.h"
#include "flecs/flecs.h"

void SpriteRenderSystem(ecs_iter_t *it);

void PlayerControllerSystem(ecs_iter_t *it);

void ProjectileSystem(ecs_iter_t *it);

extern ecs_entity_t SpriteRenderSys;
extern ecs_entity_t PlayerControllerSys;
extern ecs_entity_t ProjectileSys;

void SystemsImport(ecs_world_t *world);

#endif
