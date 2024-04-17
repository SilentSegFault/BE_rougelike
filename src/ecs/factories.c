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

ecs_id_t CreatePlayer(ecs_t *ecs, float x, float y)
{
  ecs_id_t ent = ecs_create(ecs);

  Transform *transform = ecs_add(ecs, ent, TransformComp, NULL);
  transform->position[0] = x;
  transform->position[1] = y;

  transform->size[0] = 49.0;
  transform->size[1] = 30.0;

  transform->rotation = 0;

  SpriteRender *spriteRender = ecs_add(ecs, ent, SpriteRenderComp, NULL);
  spriteRender->layer = 0;
  spriteRender->sprite.shader = GetShader("default");
  spriteRender->sprite.texture = GetTexture("soldier");
  spriteRender->sprite.colorMask[0] = 1.0f;
  spriteRender->sprite.colorMask[1] = 1.0f;
  spriteRender->sprite.colorMask[2] = 1.0f;

  Stats *stats = ecs_add(ecs, ent, StatsComp, NULL);
  stats->moveSpeed = 50;
  stats->range = 300;
  stats->damage = 10;
  stats->health = 100;

  PlayerController *playerController = ecs_add(ecs, ent, PlayerControllerComp, NULL);
  playerController->Keys.moveUp = KEY_W;
  playerController->Keys.moveDown = KEY_S;
  playerController->Keys.moveLeft = KEY_A;
  playerController->Keys.moveRight = KEY_D;
  playerController->Keys.shoot = KEY_MOUSELEFT;

  return ent;
}

ecs_id_t CreateProjectile(ecs_t *ecs, char *textureName, vec2 pos, vec2 dir, vec2 size, float rotation, float speed, float maxDistance)
{
  ecs_id_t ent = ecs_create(ecs);

  Transform *transform = ecs_add(ecs, ent, TransformComp, NULL);
  transform->position[0] = pos[0];
  transform->position[1] = pos[1];

  transform->size[0] = size[0];
  transform->size[1] = size[1];

  transform->rotation = rotation;

  SpriteRender *spriteRender = ecs_add(ecs, ent, SpriteRenderComp, NULL);
  spriteRender->layer = 0;
  spriteRender->sprite.shader = GetShader("default");
  spriteRender->sprite.texture = GetTexture(textureName);
  spriteRender->sprite.colorMask[0] = 1.0f;
  spriteRender->sprite.colorMask[1] = 1.0f;
  spriteRender->sprite.colorMask[2] = 1.0f;

  Projectile *projectile = ecs_add(ecs, ent, ProjectileComp, NULL);
  projectile->maxDistance = maxDistance;

  projectile->speed = speed;

  projectile->direction[0] = dir[0];
  projectile->direction[1] = dir[1];

  return ent;
}
