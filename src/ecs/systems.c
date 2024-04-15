#include "systems.h"
#include "components.h"
#include "../rendering/rendering_sprites.h"
#include "pico_headers/pico_log.h"

ecs_id_t SpriteRenderSys;
ecs_ret_t SpriteRenderSystem(ecs_t *ecs, ecs_id_t *entities, int entityCount, ecs_dt_t dt, void *udata)
{
  for (int i = 0; i < entityCount; i++)
  {
    ecs_id_t entID = entities[i];

    Transform *transform = ecs_get(ecs, entID, TransformComp);
    SpriteRender *spriteRender = ecs_get(ecs, entID, SpriteRenderComp);

    DrawSprite(spriteRender->sprite, transform->position, transform->size, transform->rotation);
  }

  return 0;
}

void RegisterSystems(ecs_t *ecs)
{
  log_info("Registering systems.");
  log_debug("Registering SpriteRender.");
  SpriteRenderSys = ecs_register_system(ecs, SpriteRenderSystem, NULL, NULL, NULL);
  ecs_require_component(ecs, SpriteRenderSys, TransformComp);
  ecs_require_component(ecs, SpriteRenderSys, SpriteRenderComp);
  log_debug("Systems registered.");
}
