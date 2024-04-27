#include "systems.h"
#include "flecs/flecs.h"
#include "cglm/vec2.h"
#include "components.h"
#include "../rendering/rendering_sprites.h"
#include "pico_headers/pico_log.h"
#include "../window/win32_helper.h"
#include "../utility/ut_math.h"
#include "factories.h"
#include "cute_headers/cute_c2.h"

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

  static float time = 0.0f;
  time -= it->delta_time;
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
    if(time <= 0.0f && KeyPressed(playerController[i].Keys.shoot))
    {
      time = 0.2f;
      ecs_entity_t bullet = CreateProjectile(it->world, "bullet",
                       transform[i].position, mouseDir, (vec2){10.f, 10.0f}, angle, 300.0f, stats[i].range);
      ecs_add_id(it->world, bullet, BulletTag);
    }
  }
}

void ProjectileSystem(ecs_iter_t *it)
{

  Projectile *projectile = ecs_field(it, Projectile, 1);
  Transform *transform = ecs_field(it, Transform, 2);
  Collider *collider = ecs_field(it, Collider, 3);

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

    // Initialize a filter with 2 terms on the stack
    ecs_filter_t *f = ecs_filter_init(it->world, &(ecs_filter_desc_t){
      .terms = {
        { ecs_id(Collider) },
        { BulletTag, .oper = EcsNot}
      }
    });
 
    // Iterate the filter results. Because entities are grouped by their type there
    // are two loops: an outer loop for the type, and an inner loop for the entities
    // for that type.
    ecs_iter_t cols = ecs_filter_iter(it->world, f);
    BOOL skip = FALSE;
    while (ecs_filter_next(&cols)) {
      // Each type has its own set of component arrays
      Collider *c = ecs_field(&cols, Collider, 1);
 
      // Iterate all entities for the type
      for (int j = 0; j < cols.count; j++)
      {
        if(cols.entities[j] == it->entities[i])
          continue;

        if(c2CircletoCircle(c[j].circleCollider, collider[i].circleCollider))
        {
          ecs_delete(it->world, it->entities[i]);
          skip = TRUE;
          break;
        }
      }
      if(skip)
        break;
    }
 
    ecs_filter_fini(f);

    if(skip)
      continue;

    glm_vec2_add(moveVec, transform[i].position, transform[i].position);
    collider[i].circleCollider.p.x = transform[i].position[0];
    collider[i].circleCollider.p.y = transform[i].position[1];
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
                                    {ecs_id(Collider)}
                                  },
                                .callback = ProjectileSystem
                              });

  log_debug("Systems registered.");
}
