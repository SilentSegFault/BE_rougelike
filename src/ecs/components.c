#include "components.h"
#include "pico_headers/pico_log.h"

ECS_COMPONENT_DECLARE(Transform);
ECS_COMPONENT_DECLARE(SpriteRender);
ECS_COMPONENT_DECLARE(Stats);
ECS_COMPONENT_DECLARE(PlayerController);
ECS_COMPONENT_DECLARE(Projectile);

void ComponentsImport(ecs_world_t *world)
{
  ECS_MODULE(world, Components);

  log_info("Registering components.");

  ECS_COMPONENT_DEFINE(world, Transform);
  ECS_COMPONENT_DEFINE(world, SpriteRender);
  ECS_COMPONENT_DEFINE(world, Stats);
  ECS_COMPONENT_DEFINE(world, PlayerController);
  ECS_COMPONENT_DEFINE(world, Projectile);

  log_debug("Components registered.");
}
