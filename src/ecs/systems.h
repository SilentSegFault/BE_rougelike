#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "components.h"
#include "pico_headers/pico_ecs.h"

extern ecs_id_t SpriteRenderSys;
ecs_ret_t SpriteRenderSystem(ecs_t *ecs, ecs_id_t *entities, int entityCount, ecs_dt_t dt, void *udata);

extern ecs_id_t PlayerControllerSys;
ecs_ret_t PlayerControllerSystem(ecs_t *ecs, ecs_id_t *entities, int entityCount, ecs_dt_t dt, void *udata);

extern ecs_id_t ProjectileSys;
ecs_ret_t ProjectileSystem(ecs_t *ecs, ecs_id_t *entities, int entityCount, ecs_dt_t dt, void *udata);

void RegisterSystems(ecs_t *ecs);

#endif
