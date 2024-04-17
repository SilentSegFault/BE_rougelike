#ifndef FACTORIES_H
#define FACTORIES_H

#include "pico_headers/pico_ecs.h"
#include "cglm/cglm.h"

ecs_id_t CreateSmiley(ecs_t *ecs, float x, float y);
ecs_id_t CreatePlayer(ecs_t *ecs, float x, float y);
ecs_id_t CreateProjectile(ecs_t *ecs, char *textureName, vec2 pos, vec2 dir, vec2 size, float rotation, float speed, float maxDistance);

#endif
