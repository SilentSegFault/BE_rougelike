#include "components.h"
#include "pico_headers/pico_log.h"

ecs_id_t TransformComp;
ecs_id_t SpriteRenderComp;

void RegisterComponents(ecs_t *ecs)
{
  log_info("Registering components.");
  log_debug("Registering Transform component.");
  TransformComp = ecs_register_component(ecs, sizeof(Transform), NULL, NULL);
  log_debug("Registering SpriteRender component.");
  SpriteRenderComp = ecs_register_component(ecs, sizeof(SpriteRender), NULL, NULL);
  log_debug("Components registered.");
}
