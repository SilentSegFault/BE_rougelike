#include "factories.h"
#include "components.h"
#include "../resource_manager/resource_manager.h"
#include "pico_headers/pico_log.h"

ecs_id_t CreateSmiley(ecs_t *ecs, float x, float y)
{
  ecs_id_t ent = ecs_create(ecs);

  Transform *transform = ecs_add(ecs, ent, TransformComp, NULL);
  transform->position[0] = x;
  transform->position[1] = y;
  log_debug("transform component: %p, x = %f, y = %f", transform, x, y);

  transform->size[0] = 30.0;
  transform->size[1] = 30.0;

  transform->rotation = 0;

  SpriteRender *spriteRender = ecs_add(ecs, ent, SpriteRenderComp, NULL);
  spriteRender->layer = 0;
  spriteRender->sprite.shader = GetShader("default");
  spriteRender->sprite.texture = GetTexture("smiley");
  spriteRender->sprite.colorMask[0] = 1.0f;
  spriteRender->sprite.colorMask[1] = 1.0f;
  spriteRender->sprite.colorMask[2] = 1.0f;

  return ent;
}
