#include "systems.h"
#include "components.h"
#include "../rendering/rendering_sprites.h"
#include "../window/window.h"

ECS_SYSTEM_DECLARE(SpriteRenderSystem);

void SpriteRenderSystem(ecs_iter_t *it)
{
  SpriteRender *spriteRender = ecs_field(it, SpriteRender, 1);
  Transform *transform = ecs_field(it, Transform, 2);


  for(int i = 0; i < it->count; i++)
  {
    if(spriteRender[i].visible)
      DrawSprite(spriteRender[i].sprite,
                 GetProjectionMatrix(),
                 transform[i].position,
                 transform[i].size,
                 transform[i].rotation,
                 spriteRender[i].flipX,
                 spriteRender[i].flipY);
  }
}
void SystemsModuleImport(ecs_world_t *world)
{
  ECS_MODULE(world, SystemsModule);

  ECS_SYSTEM_DEFINE(world, SpriteRenderSystem, 0, SpriteRender, Transform);
}
