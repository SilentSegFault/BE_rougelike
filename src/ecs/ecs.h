#ifndef ECS_H
#define ECS_H

#include <stdint.h>

#define ECS_MAX_ENTITIES 1024
#define ECS_MAX_SYSTEMS 16
#define ECS_MAX_COMPONENTS 32

#define IS_ALIVE_BIT (1 << 0)


typedef uint32_t EcsID;
typedef uint16_t EcsEntity;
typedef struct EcsWorld EcsWorld;
typedef struct EcsSystem EcsSystem;

typedef void(*EcsCallback)(EcsWorld *world, EcsID *entities, unsigned long long entityCount, float deltaTime);

struct EcsSystem
{
  uint16_t requiredComponents;
  EcsCallback callback;
};

typedef struct
{
  size_t size;
  unsigned int mask;
  void **data;
} EcsComponent;

struct EcsWorld
{
  EcsID *idStack;
  unsigned long nextId;
  EcsEntity *entities;
  EcsSystem *systems;
  unsigned int numOfSystems;
  EcsComponent *components;
  unsigned int numOfComponents;
};

EcsWorld* EcsCreateWorld();
void EcsFreeWorld(EcsWorld *world);

EcsID EcsCreateEntity(EcsWorld *world);
void EcsDestroyEntity(EcsWorld *world, EcsID entity);
int EcsIsEntitiyAlive(EcsWorld *world, EcsID entity);

void* EcsAddComponent(EcsWorld *world, EcsID entity, EcsID component);
void EcsRemoveComponent(EcsWorld *world, EcsID entity, EcsID component);
int EcsHasComponent(EcsWorld *world, EcsID entity, EcsID component);
void* EcsGetComponent(EcsWorld *world, EcsID entity, EcsID component);

EcsID EcsRegisterComponent(EcsWorld *world, size_t compSize);
EcsID EcsRegisterSystem(EcsWorld *world, EcsCallback callback);

void EcsRequireComponent(EcsWorld *world, EcsID system, EcsID component);

void EcsUpdateSystem(EcsWorld *world, EcsID system, float dt);

#endif
