#include "components.h"
#include "pico_headers/pico_log.h"

ecs_id_t TransformComp;
ecs_id_t SpriteRenderComp;
ecs_id_t StatsComp;
ecs_id_t PlayerControllerComp;
ecs_id_t ProjectileComp;
ecs_id_t BoxColliderComp;

void RegisterComponents(ecs_t *ecs)
{
  log_info("Registering components.");

  TransformComp = ecs_register_component(ecs, sizeof(Transform), NULL, NULL);
  SpriteRenderComp = ecs_register_component(ecs, sizeof(SpriteRender), NULL, NULL);
  StatsComp = ecs_register_component(ecs, sizeof(Stats), NULL, NULL);
  PlayerControllerComp = ecs_register_component(ecs, sizeof(PlayerController), NULL, NULL);
  ProjectileComp = ecs_register_component(ecs, sizeof(Projectile), NULL, NULL);
  BoxColliderComp = ecs_register_component(ecs, sizeof(BoxCollider), NULL, NULL);

  log_debug("Components registered.");
}
