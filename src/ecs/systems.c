#include "systems.h"
#include "cglm/vec2.h"
#include "components.h"
#include "../rendering/rendering_sprites.h"
#include "pico_headers/pico_log.h"
#include "../window/win32_helper.h"
#include "../utility/ut_math.h"
#include "factories.h"

ecs_id_t SpriteRenderSys;
ecs_ret_t SpriteRenderSystem(ecs_t *ecs, ecs_id_t *entities, int entityCount, ecs_dt_t dt, void *udata)
{
  for (int i = 0; i < entityCount; i++)
  {
    ecs_id_t entID = entities[i];

    Transform *transform = ecs_get(ecs, entID, TransformComp);
    SpriteRender *spriteRender = ecs_get(ecs, entID, SpriteRenderComp);

    vec2 pos = {transform->position[0] - transform->size[0] * 0.5f, transform->position[1] - transform->size[1] * 0.5f};
    DrawSprite(spriteRender->sprite, pos, transform->size, transform->rotation);
  }

  return 0;
}

ecs_id_t PlayerControllerSys;
ecs_ret_t PlayerControllerSystem(ecs_t *ecs, ecs_id_t *entities, int entityCount, ecs_dt_t dt, void *udata)
{
  for(int i = 0; i < entityCount; i++)
  {
    ecs_id_t entID = entities[i];

    PlayerController *playerController = ecs_get(ecs, entID, PlayerControllerComp);
    Transform *transform = ecs_get(ecs, entID, TransformComp);
    Stats *stats = ecs_get(ecs, entID, StatsComp);

    // Movement
    vec2 movementVec = {0.0f, 0.0f};
    BOOL playerMoved = FALSE;
    if(KeyPressed(playerController->Keys.moveUp))
    {
      playerMoved = TRUE;
      movementVec[1] -= 1;
    }

    
    if(KeyPressed(playerController->Keys.moveDown))
    {
      playerMoved = TRUE;
      movementVec[1] += 1;

    }

    if(KeyPressed(playerController->Keys.moveLeft))
    {
      playerMoved = TRUE;
      movementVec[0] -= 1;

    }

    if(KeyPressed(playerController->Keys.moveRight))
    {
      playerMoved = TRUE;
      movementVec[0] += 1;

    }

    if(playerMoved)
    {
      glm_vec2_scale_as(movementVec, stats->moveSpeed * dt, movementVec);
      glm_vec2_add(movementVec, transform->position, transform->position);
    }

    // Rotation
    vec2 vecRight = {1.0f, 0.0f};
    vec2 mouseDir;
    glm_vec2_sub((vec2){mouseX, mouseY}, transform->position, mouseDir);
    float angle = GetAngleBetweenVectors(vecRight, mouseDir);
    transform->rotation = angle;

    // Shooting
    if(KeyDown(playerController->Keys.shoot))
    {
      CreateProjectile(ecs, "bullet",
                       transform->position, mouseDir, (vec2){10.f, 10.0f}, angle, 300.0f, stats->range);
    }
  }

  return 0;
}

ecs_id_t ProjectileSys;
ecs_ret_t ProjectileSystem(ecs_t *ecs, ecs_id_t *entities, int entityCount, ecs_dt_t dt, void *udata)
{

  for(int i = 0; i < entityCount; i++)
  {
    ecs_id_t entID = entities[i];

    Transform *transform = ecs_get(ecs, entID, TransformComp);
    Projectile *projectile = ecs_get(ecs, entID, ProjectileComp);

    if(projectile->maxDistance <= 0)
    {
      ecs_queue_destroy(ecs, entID);
      continue;
    }

    vec2 moveVec;
    glm_vec2_scale_as(projectile->direction, projectile->speed * dt, moveVec);
    float distance = glm_vec2_norm(moveVec);

    glm_vec2_add(moveVec, transform->position, transform->position);
    projectile->maxDistance -= distance;
  }


  return 0;
}

void RegisterSystems(ecs_t *ecs)
{
  log_info("Registering systems.");
  SpriteRenderSys = ecs_register_system(ecs, SpriteRenderSystem, NULL, NULL, NULL);
  ecs_require_component(ecs, SpriteRenderSys, TransformComp);
  ecs_require_component(ecs, SpriteRenderSys, SpriteRenderComp);

  PlayerControllerSys = ecs_register_system(ecs, PlayerControllerSystem, NULL, NULL, NULL);
  ecs_require_component(ecs, PlayerControllerSys, PlayerControllerComp);
  ecs_require_component(ecs, PlayerControllerSys, TransformComp);
  ecs_require_component(ecs, PlayerControllerSys, StatsComp);

  ProjectileSys = ecs_register_system(ecs, ProjectileSystem, NULL, NULL, NULL);
  ecs_require_component(ecs, ProjectileSys, ProjectileComp);
  ecs_require_component(ecs, ProjectileSys, TransformComp);

  log_debug("Systems registered.");
}
