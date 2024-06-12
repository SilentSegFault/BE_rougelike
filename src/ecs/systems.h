#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "ecs.h"

void system_Start(EcsWorld *world, EcsID *entities, unsigned long long numOfEntities, float deltaTime);
void system_Update(EcsWorld *world, EcsID *entities, unsigned long long numOfEntities, float deltaTime);
void system_Destroy(EcsWorld *world, EcsID *entities, unsigned long long numOfEntities, float deltaTime);
void system_RenderSprites(EcsWorld *world, EcsID *entities, unsigned long long numOfEntities, float deltaTime);
void system_RenderTilemap(EcsWorld *world, EcsID *entities, unsigned long long numOfEntities, float deltaTime);
void system_RenderText(EcsWorld *world, EcsID *entities, unsigned long long numOfEntities, float deltaTime);
void system_Animation(EcsWorld *world, EcsID *entities, unsigned long long numOfEntities, float deltaTime);
void system_AnimationRender(EcsWorld *world, EcsID *entities, unsigned long long numOfEntities, float deltaTime);
void system_CollisionTest(EcsWorld *world, EcsID *entities, unsigned long long numOfEntities, float deltaTime);

void system_RenderDebugCollider(EcsWorld *world, EcsID *entities, unsigned long long numOfEntities, float deltaTime);

extern EcsID StartSystem;
extern EcsID UpdateSystem;
extern EcsID DestroySystem;
extern EcsID SpriteRenderSystem;
extern EcsID TilemapRenderSystem;
extern EcsID TextRenderSystem;
extern EcsID AnimationSystem;
extern EcsID AnimationRenderSystem;
extern EcsID CollisionSystem;

extern EcsID RenderDebugColliderSystem;

void RegisterSystems(EcsWorld *world);

#endif
