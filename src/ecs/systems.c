#include "systems.h"
#include "components.h"
#include "../rendering/rendering_sprites.h"
#include "../rendering/rendering_tilemaps.h"
#include "../rendering/rendering_text.h"
#include "../window/window.h"
#include "../resource_management/assets_library.h"
#include "cglm/cglm.h"

ECS_SYSTEM_DECLARE(SpriteRenderSystem);

void SpriteRenderSystem(ecs_iter_t *it)
{
  SpriteRender *spriteRender = ecs_field(it, SpriteRender, 1);
  Transform *transform = ecs_field(it, Transform, 2);


  for(int i = 0; i < it->count; i++)
  {
    if(spriteRender[i].visible)
    {
      vec2 parentPos = {0, 0};
      ecs_entity_t parent = transform[i].parent;
      while(parent != 0)
      {
        const Transform *parentTransform = ecs_get_id(it->world, parent, ecs_id(Transform));
        parentPos[0] += parentTransform->position[0];
        parentPos[1] += parentTransform->position[1];

        parent = parentTransform->parent;
      }
      vec2 pos = {transform[i].position[0] + parentPos[0] - transform[i].size[0] * 0.5f,
                  transform[i].position[1] + parentPos[1] - transform[i].size[1] * 0.5f};

      DrawSprite(spriteRender[i].sprite,
                 GetProjectionMatrix(),
                 pos,
                 transform[i].size,
                 transform[i].rotation,
                 spriteRender[i].flipX,
                 spriteRender[i].flipY);
    }
  }
}

ECS_SYSTEM_DECLARE(TilemapRenderSystem);

void TilemapRenderSystem(ecs_iter_t *it)
{
  TilemapRender *tilemapRender = ecs_field(it, TilemapRender, 1);
  Transform *transform = ecs_field(it, Transform, 2);

  for(int i = 0; i < it->count; i++)
  {
    DrawTilemap(tilemapRender[i].tilemap,
                GetShader("tilemap"),
                GetProjectionMatrix(),
                transform[i].position,
                transform[i].size,
                transform[i].rotation);
  }
}

ECS_SYSTEM_DECLARE(TextRenderSystem);

void TextRenderSystem(ecs_iter_t *it)
{
  TextRender *textRender = ecs_field(it, TextRender, 1);
  Transform *transform = ecs_field(it, Transform, 2);

  for (int i = 0; i < it->count; i++)
  {
    RenderText(GetShader("text"),
               GetProjectionMatrix(),
               GetFont(textRender[i].font),
               textRender[i].text,
               transform[i].position,
               textRender[i].scale,
               textRender[i].color);
  }
}

void SystemsModuleImport(ecs_world_t *world)
{
  ECS_MODULE(world, SystemsModule);

  ECS_SYSTEM_DEFINE(world, SpriteRenderSystem, 0, SpriteRender, Transform);
  ECS_SYSTEM_DEFINE(world, TilemapRenderSystem, 0, TilemapRender, Transform);
  ECS_SYSTEM_DEFINE(world, TextRenderSystem, 0, TextRender, Transform);
}
