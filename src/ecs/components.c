#include "components.h"

ECS_COMPONENT_DECLARE(Transform);
ECS_COMPONENT_DECLARE(SpriteRender);
ECS_COMPONENT_DECLARE(TilemapRender);
ECS_COMPONENT_DECLARE(Stats);
ECS_COMPONENT_DECLARE(Collider);

void ComponentsModuleImport(ecs_world_t *world)
{
  ECS_MODULE(world, ComponentsModule);

  ECS_COMPONENT_DEFINE(world, Transform);
  ECS_COMPONENT_DEFINE(world, SpriteRender);
  ECS_COMPONENT_DEFINE(world, TilemapRender);
  ECS_COMPONENT_DEFINE(world, Stats);
  ECS_COMPONENT_DEFINE(world, Collider);
}
