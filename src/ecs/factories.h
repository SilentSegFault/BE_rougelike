#ifndef FACTORIES_H
#define FACTORIES_H

#include "flecs/flecs.h"
#include "cglm/types.h"

ecs_entity_t CreateEntity(ecs_world_t *world, const char *entity, const char *name, vec2 position, float rotation, const char *parent);

#endif
