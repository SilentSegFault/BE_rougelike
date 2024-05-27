#ifndef FACTORIES_H
#define FACTORIES_H

#include "flecs/flecs.h"
#include "cglm/types.h"

ecs_entity_t CreateEntity(ecs_world_t *world, const char *entity, vec2 position, float rotation);

#endif
