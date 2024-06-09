#ifndef FACTORIES_H
#define FACTORIES_H

#include "cglm/types.h"
#include "ecs.h"

EcsID CreateEntity(EcsWorld *world, const char *entity, vec2 position, float rotation, const char *parent);
#endif
