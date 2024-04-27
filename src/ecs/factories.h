#ifndef FACTORIES_H
#define FACTORIES_H

#include "cglm/cglm.h"
#include "flecs/flecs.h"

ecs_entity_t CreateSmiley(ecs_world_t *world, float x, float y);
ecs_entity_t CreatePlayer(ecs_world_t *world, float x, float y);
ecs_entity_t CreateProjectile(ecs_world_t *world, char *textureName, vec2 pos, vec2 dir,
                              vec2 size, float rotation, float speed, float maxDistance);

#endif
