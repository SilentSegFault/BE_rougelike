#include "components.h"
#include "ecs.h"

EcsID TransformComp;
EcsID SpriteRenderComp;
EcsID TilemapRenderComp;
EcsID TextRenderComp;
EcsID AnimatorComp;
EcsID StatsComp;
EcsID ColliderComp;
EcsID GameObjectComp;

EcsID NewTag;
EcsID UpdateTag;
EcsID DestroyTag;

void RegisterComponents(EcsWorld *world)
{
  TransformComp = EcsRegisterComponent(world, sizeof(Transform));
  SpriteRenderComp = EcsRegisterComponent(world, sizeof(SpriteRender));
  TilemapRenderComp = EcsRegisterComponent(world, sizeof(TilemapRender));
  TextRenderComp = EcsRegisterComponent(world, sizeof(TextRender));
  AnimatorComp = EcsRegisterComponent(world, sizeof(Animator));
  StatsComp = EcsRegisterComponent(world, sizeof(Stats));
  ColliderComp = EcsRegisterComponent(world, sizeof(Collider));
  GameObjectComp = EcsRegisterComponent(world, sizeof(GameObject));

  NewTag = EcsRegisterComponent(world, 1);
  UpdateTag = EcsRegisterComponent(world, 1);
  DestroyTag = EcsRegisterComponent(world, 1);
}
