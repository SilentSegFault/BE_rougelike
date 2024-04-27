#include "factories.h"
#include "components.h"
#include "../resource_manager/resource_manager.h"
#include "pico_headers/pico_log.h"

ecs_entity_t CreateSmiley(ecs_world_t *world, float x, float y)
{
  ecs_entity_t ent = ecs_new_id(world);

  ecs_add(world, ent, Transform);

  ecs_set(world, ent, Transform,
          {
            .position = {x, y},
            .size = {30.0f, 30.0f},
            .rotation = 0
          });

  ecs_add(world, ent, SpriteRender);

  ecs_set(world, ent, SpriteRender,
          {
            .layer = 0,
            .sprite =
              {
                .shader = GetShader("default"),
                .texture = GetTexture("smiley"),
                .colorMask = {1.0f, 1.0f, 1.0f}
              }
          });

  return ent;
}

ecs_entity_t CreatePlayer(ecs_world_t *world, float x, float y)
{
  ecs_entity_t ent = ecs_new_id(world);

  ecs_add(world, ent, Transform);

  ecs_set(world, ent, Transform,
          {
            .position = {x, y},
            .size = {49.0f, 30.0f},
            .rotation = 0
          });

  ecs_add(world, ent, SpriteRender);

  ecs_set(world, ent, SpriteRender,
          {
            .layer = 0,
            .sprite =
              {
                .shader = GetShader("default"),
                .texture = GetTexture("soldier"),
                .colorMask = {1.0f, 1.0f, 1.0f}
              }
          });

  ecs_add(world, ent, Stats);

  ecs_set(world, ent, Stats,
          {
            .moveSpeed = 50,
            .range = 300,
            .damage = 10,
            .health = 100
          });

  ecs_add(world, ent, PlayerController);

  ecs_set(world, ent, PlayerController,
          {
            .Keys =
              {
                .moveUp = KEY_W,
                .moveDown = KEY_S,
                .moveLeft = KEY_A,
                .moveRight = KEY_D,
                .shoot = KEY_MOUSELEFT
              }
          });

  return ent;
}

ecs_entity_t CreateProjectile(ecs_world_t *world, char *textureName, vec2 pos, vec2 dir,
                              vec2 size, float rotation, float speed, float maxDistance)
{
  ecs_entity_t ent = ecs_new_id(world);
  
  ecs_add(world, ent, Transform);

  ecs_set(world, ent, Transform,
          {
            .position = {pos[0], pos[1]},
            .size = {size[0], size[1]},
            .rotation = rotation
          });

  ecs_add(world, ent, SpriteRender);

  ecs_set(world, ent, SpriteRender,
          {
            .layer = 0,
            .sprite =
              {
                .shader = GetShader("default"),
                .texture = GetTexture(textureName),
                .colorMask = {1.0f, 1.0f, 1.0f}
              }
          });

  ecs_add(world, ent, Projectile);

  ecs_set(world, ent, Projectile,
          {
            .maxDistance = maxDistance,
            .speed = speed,
            .direction = {dir[0], dir[1]}
          });

  return ent;
}
