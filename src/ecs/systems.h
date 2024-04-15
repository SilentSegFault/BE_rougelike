#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "pico_headers/pico_ecs.h"

extern ecs_id_t SpriteRenderSys;
ecs_ret_t SpriteRenderSystem(ecs_t *ecs, ecs_id_t *entities, int entityCount, ecs_dt_t dt, void *udata);

void RegisterSystems(ecs_t *ecs);

#endif
