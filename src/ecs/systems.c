#include "systems.h"
#include "flecs/flecs.h"
#include "cglm/vec2.h"
#include "components.h"
#include "../rendering/rendering_sprites.h"
#include "pico_headers/pico_log.h"
#include "../window/win32_helper.h"
#include "../utility/ut_math.h"
#include "factories.h"

void SpriteRenderSystem(ecs_iter_t *it)
{
  Transform *transform = ecs_field(it, Transform, 1);
  SpriteRender *spriteRender = ecs_field(it, SpriteRender, 2);

  for(int i = 0; i < it->count; i++)
  {
    vec2 pos = {transform[i].position[0] - transform[i].size[0] * 0.5f, transform[i].position[1] - transform[i].size[1] * 0.5f};
    DrawSprite(spriteRender[i].sprite, pos, transform[i].size, transform[i].rotation);
  }
}

void PlayerControllerSystem(ecs_iter_t *it)
{

  PlayerController *playerController = ecs_field(it, PlayerController, 1);
  Transform *transform = ecs_field(it, Transform, 2);
  Stats *stats = ecs_field(it, Stats, 3);

  for(int i = 0; i < it->count; i++)
  {
    // Movement
    vec2 movementVec = {0.0f, 0.0f};
    BOOL playerMoved = FALSE;
    if(KeyPressed(playerController[i].Keys.moveUp))
    {
      playerMoved = TRUE;
      movementVec[1] -= 1;
    }

    
    if(KeyPressed(playerController[i].Keys.moveDown))
    {
      playerMoved = TRUE;
      movementVec[1] += 1;

    }

    if(KeyPressed(playerController[i].Keys.moveLeft))
    {
      playerMoved = TRUE;
      movementVec[0] -= 1;

    }

    if(KeyPressed(playerController[i].Keys.moveRight))
    {
      playerMoved = TRUE;
      movementVec[0] += 1;

    }

    if(playerMoved)
    {
      glm_vec2_scale_as(movementVec, stats[i].moveSpeed * it->delta_time, movementVec);
      glm_vec2_add(movementVec, transform[i].position, transform[i].position);
    }

    // Rotation
    vec2 vecRight = {1.0f, 0.0f};
    vec2 mouseDir;
    glm_vec2_sub((vec2){mouseX, mouseY}, transform[i].position, mouseDir);
    float angle = GetAngleBetweenVectors(vecRight, mouseDir);
    transform[i].rotation = angle;

    // Shooting
    if(KeyDown(playerController[i].Keys.shoot))
    {
      CreateProjectile(it->world, "bullet",
                       transform[i].position, mouseDir, (vec2){10.f, 10.0f}, angle, 300.0f, stats[i].range);
    }
  }
}

void ProjectileSystem(ecs_iter_t *it)
{

  Projectile *projectile = ecs_field(it, Projectile, 1);
  Transform *transform = ecs_field(it, Transform, 2);

  for(int i = 0; i < it->count; i++)
  {
    if(projectile[i].maxDistance <= 0)
    {
      ecs_delete(it->world, it->entities[i]);
      continue;
    }

    vec2 moveVec;
    glm_vec2_scale_as(projectile[i].direction, projectile[i].speed * it->delta_time, moveVec);
    float distance = glm_vec2_norm(moveVec);

    glm_vec2_add(moveVec, transform[i].position, transform[i].position);
    projectile[i].maxDistance -= distance;
  }
}

ecs_entity_t SpriteRenderSys;
ecs_entity_t PlayerControllerSys;
ecs_entity_t ProjectileSys;

void SystemsImport(ecs_world_t *world)
{
  ECS_MODULE(world, Systems);

  log_info("Registering systems.");

  SpriteRenderSys = ecs_system(world, 
                              {
                                .query.filter.terms = 
                                  {
                                    {ecs_id(Transform)},
                                    {ecs_id(SpriteRender)},
                                  },
                                .callback = SpriteRenderSystem
                              });

  PlayerControllerSys = ecs_system(world, 
                              {
                                .query.filter.terms = 
                                  {
                                    {ecs_id(PlayerController)},
                                    {ecs_id(Transform)},
                                    {ecs_id(Stats)},
                                  },
                                .callback = PlayerControllerSystem
                              });

 ProjectileSys = ecs_system(world, 
                              {
                                .query.filter.terms = 
                                  {
                                    {ecs_id(Projectile)},
                                    {ecs_id(Transform)},
                                  },
                                .callback = ProjectileSystem
                              });

  log_debug("Systems registered.");
}
