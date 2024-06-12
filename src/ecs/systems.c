#include "systems.h"
#include "components.h"
#include "components_util.h"
#include "../rendering/rendering_sprites.h"
#include "../rendering/rendering_tilemaps.h"
#include "../rendering/rendering_text.h"
#include "../rendering/rendering_debug.h"
#include "../scripting/script_engine.h"
#include "../window/window.h"
#include "../resource_management/assets_library.h"
#include "ecs.h"
#include "../logger/logger.h"

void system_Start(EcsWorld *world, EcsID *entities, unsigned long long numOfEntities, float deltaTime)
{
  for(int i = 0; i < numOfEntities; i++)
  {
    EcsID e = entities[i];
    CallOnStart(e);
    EcsRemoveComponent(world, e, NewTag);
  }
}

void system_Update(EcsWorld *world, EcsID *entities, unsigned long long numOfEntities, float deltaTime)
{
  for(int i = 0; i < numOfEntities; i++)
  {
    EcsID e = entities[i];
    CallOnUpdate(e, deltaTime);
  }
}

void system_Destroy(EcsWorld *world, EcsID *entities, unsigned long long numOfEntities, float deltaTime)
{
  for(int i = 0; i < numOfEntities; i++)
  {
    EcsID e = entities[i];
    CallOnDestroy(e);
    CallRemoveEntity(e);
    EcsDestroyEntity(world, e);
  }
}

void system_RenderSprites(EcsWorld *world, EcsID *entities, unsigned long long numOfEntities, float deltaTime)
{
  for(int i = 0; i < numOfEntities; i++)
  {
    EcsID e = entities[i];
    SpriteRender *spriteRender = EcsGetComponent(world, e, SpriteRenderComp);
    if(spriteRender->visible)
    {
      Transform *transform = EcsGetComponent(world, e, TransformComp);

      float scale = GetGameWindowHeight() / 1080.f;
      vec2 size = {transform->size[0] * transform->scale[0],
                   transform->size[1] * transform->scale[1]};

      vec2 pos = {(transform->position[0] - (size[0] * 0.5f)) * scale,
                  (transform->position[1] - (size[1] * 0.5f)) * scale};

      size[0] *= scale;
      size[1] *= scale;
      
      DrawSprite(spriteRender->sprite,
                 GetProjectionMatrix(),
                 spriteRender->drawLayer,
                 pos,
                 size,
                 transform->rotation,
                 spriteRender->flipX,
                 spriteRender->flipY);
    }
  }
}

void system_RenderTilemap(EcsWorld *world, EcsID *entities, unsigned long long numOfEntities, float deltaTime)
{
  for(int i = 0; i < numOfEntities; i++)
  {
    EcsID e = entities[i];

    TilemapRender *tilemapRender = EcsGetComponent(world, e, TilemapRenderComp);
    Transform *transform = EcsGetComponent(world, e, TransformComp);

    float scale = GetGameWindowHeight() / 1080.f;

    vec2 pos = {transform->position[0] * scale, transform->position[1] * scale};
    vec2 size = {transform->size[0] * transform->scale[0] * scale, transform->size[1] * transform->scale[1] * scale};

    DrawTilemap(tilemapRender->tilemap,
                GetShader("tilemap"),
                GetProjectionMatrix(),
                pos,
                size,
                transform->rotation);
  }
}

void system_RenderText(EcsWorld *world, EcsID *entities, unsigned long long numOfEntities, float deltaTime)
{
  for (int i = 0; i < numOfEntities; i++)
  {
    EcsID e = entities[i];

    TextRender *textRender = EcsGetComponent(world, e, TextRenderComp);
    Transform *transform = EcsGetComponent(world, e, TransformComp);

    float scale = GetGameWindowHeight() / 1080.f;
    vec2 pos = {transform->position[0] * scale, transform->position[1] * scale};

    RenderText(GetShader("text"),
               GetProjectionMatrix(),
               textRender->drawLayer,
               GetFont(textRender->font),
               textRender->text,
               pos,
               textRender->scale * scale,
               textRender->color);
  }
}

void system_AnimationRender(EcsWorld *world, EcsID *entities, unsigned long long numOfEntities, float deltaTime)
{
  for(int i = 0; i < numOfEntities; i++)
  {
    EcsID e = entities[i];

    Animator *animator = EcsGetComponent(world, e, AnimatorComp);
    Transform *transform = EcsGetComponent(world, e, TransformComp);

    float scale = GetGameWindowHeight() / 1080.f;
    vec2 size = {(transform->size[0] * transform->scale[0]),
      (transform->size[1] * transform->scale[1])};

    vec2 pos = {(transform->position[0] - (size[0] * 0.5f)) * scale,
      (transform->position[1] - (size[1] * 0.5f)) * scale};

    size[0] *= scale;
    size[1] *= scale;

    DrawSpritesheetFrame(animator->currentAnimation->spritesheet,
                         GetProjectionMatrix(),
                         animator->drawLayer,
                         animator->currentAnimation->row,
                         animator->currentFrame,
                         pos,
                         size,
                         transform->rotation,
                         animator->flip);
  }
}

void system_Animation(EcsWorld *world, EcsID *entities, unsigned long long numOfEntities, float deltaTime)
{
  for(int i = 0; i < numOfEntities; i++)
  {
    EcsID e = entities[i];

    Animator *animator = EcsGetComponent(world, e, AnimatorComp);

    if(animator->playOnce && animator->currentFrame >= animator->currentAnimation->frames)
    {
      continue;
    }

    animator->frameCounter++;
    if(animator->frameCounter % animator->currentAnimation->speed == 0)
    {
      animator->currentFrame = animator->currentFrame + 1;
      if(!animator->playOnce)
      {
        animator->currentFrame %= animator->currentAnimation->frames;
      }
      animator->frameCounter = 0;
    }
  }
}

void system_CollisionTest(EcsWorld *world, EcsID *entities, unsigned long long numOfEntities, float deltaTime)
{
  for(int i = 0; i < numOfEntities; i++)
  {
    for (int j = i + 1; j < numOfEntities; j++)
    {
      if(AreColliding(world, entities[i], entities[j]))
      {
        CallOnCollision(entities[i], entities[j]);
        CallOnCollision(entities[j], entities[i]);
      }
    }
  }
}

void system_RenderDebugCollider(EcsWorld *world, EcsID *entities, unsigned long long numOfEntities, float deltaTime)
{
  for(int i = 0; i < numOfEntities; i++)
  {
    EcsID e = entities[i];

    Transform *transform = EcsGetComponent(world, e, TransformComp);
    Collider *collider = EcsGetComponent(world, e, ColliderComp);

    float scale = GetGameWindowHeight() / 1080.f;

    vec2 size = {(transform->size[0] * transform->scale[0]),
      (transform->size[1] * transform->scale[1])};

    vec2 colSize = {collider->width * scale, collider->height * scale};

    vec2 pos = {(transform->position[0] - (collider->width * 0.5f)) * scale,
      (transform->position[1] - (collider->height * 0.5f)) * scale};

    vec3 color = {0.0f, 1.0f, 0.0f};

    DrawRect(GetProjectionMatrix(), pos, colSize, 0, color);
  }
}

EcsID StartSystem;
EcsID UpdateSystem;
EcsID DestroySystem;
EcsID SpriteRenderSystem;
EcsID TilemapRenderSystem;
EcsID TextRenderSystem;
EcsID AnimationSystem;
EcsID AnimationRenderSystem;
EcsID CollisionSystem;

EcsID RenderDebugColliderSystem;

void RegisterSystems(EcsWorld *world)
{
  StartSystem = EcsRegisterSystem(world, system_Start);
  UpdateSystem = EcsRegisterSystem(world, system_Update);
  DestroySystem = EcsRegisterSystem(world, system_Destroy);
  SpriteRenderSystem = EcsRegisterSystem(world, system_RenderSprites);
  TilemapRenderSystem = EcsRegisterSystem(world, system_RenderTilemap);
  TextRenderSystem = EcsRegisterSystem(world, system_RenderText);
  AnimationSystem = EcsRegisterSystem(world, system_Animation);
  AnimationRenderSystem = EcsRegisterSystem(world, system_AnimationRender);
  CollisionSystem = EcsRegisterSystem(world, system_CollisionTest);
  RenderDebugColliderSystem = EcsRegisterSystem(world, system_RenderDebugCollider);

  //StartSystem
  EcsRequireComponent(world, StartSystem, NewTag);

  //UpdateSystem
  EcsRequireComponent(world, UpdateSystem, UpdateTag);

  //DestroySytem
  EcsRequireComponent(world, DestroySystem, DestroyTag);

  //SpriteRenderSystem
  EcsRequireComponent(world, SpriteRenderSystem, SpriteRenderComp);
  EcsRequireComponent(world, SpriteRenderSystem, TransformComp);

  //TilemapRenderSystem
  EcsRequireComponent(world, TilemapRenderSystem, TilemapRenderComp);
  EcsRequireComponent(world, TilemapRenderSystem, TransformComp);
  
  //TextRenderSystem
  EcsRequireComponent(world, TextRenderSystem, TextRenderComp);
  EcsRequireComponent(world, TextRenderSystem, TransformComp);

  //AnimationSystem
  EcsRequireComponent(world, AnimationSystem, AnimatorComp);

  //AnimationRenderSystem
  EcsRequireComponent(world, AnimationRenderSystem, AnimatorComp);
  EcsRequireComponent(world, AnimationRenderSystem, TransformComp);

  //CollisionSystem
  EcsRequireComponent(world, CollisionSystem, ColliderComp);
  EcsRequireComponent(world, CollisionSystem, TransformComp);

  //RenderDebugColliderSystem
  EcsRequireComponent(world, RenderDebugColliderSystem, TransformComp);
  EcsRequireComponent(world, RenderDebugColliderSystem, ColliderComp);
}
