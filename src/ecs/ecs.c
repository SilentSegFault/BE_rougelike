#include "ecs.h"
#include <stdlib.h>

EcsWorld* EcsCreateWorld()
{
  EcsWorld *world = calloc(1, sizeof(EcsWorld));
  world->idStack = malloc(sizeof(EcsID) * ECS_MAX_ENTITIES);

  for(int i = 0; i < ECS_MAX_ENTITIES; i++)
  {
    world->idStack[i] = i;
  }
  world->nextId = ECS_MAX_ENTITIES - 1;
  world->systems = calloc(ECS_MAX_SYSTEMS, sizeof(EcsSystem));
  world->numOfSystems = 0;
  world->entities = calloc(ECS_MAX_ENTITIES, sizeof(EcsEntity));
  world->components = calloc(ECS_MAX_COMPONENTS, sizeof(EcsComponent));
  world->numOfComponents = 0;

  return world;
}

void EcsFreeWorld(EcsWorld *world)
{
  for(int i = 0; i < world->numOfComponents; i++)
  {
    free(world->components[i].data);
  }
  free(world->components);
  free(world->systems);
  free(world->entities);
  free(world->idStack);
}

EcsID EcsCreateEntity(EcsWorld *world)
{
  EcsID id = world->idStack[world->nextId--];
  world->entities[id] |= IS_ALIVE_BIT;
  return id;
}

int EcsIsEntitiyAlive(EcsWorld *world, EcsID entity)
{
  return world->entities[entity] & IS_ALIVE_BIT;
}

void EcsDestroyEntity(EcsWorld *world, EcsID entity)
{
  //TODO: clear all components data!!!!

  if(!EcsIsEntitiyAlive(world, entity))
    return;

  world->entities[entity] = 0;
  world->idStack[--world->nextId] = entity;
}

EcsID EcsRegisterComponent(EcsWorld *world, size_t compSize)
{
  EcsID compId = world->numOfComponents;
  world->components[world->numOfComponents].size = compSize;
  world->components[world->numOfComponents].mask = (1 << (1 + world->numOfComponents));
  world->components[world->numOfComponents].data = calloc(ECS_MAX_ENTITIES, sizeof(void*));
  world->numOfComponents++;
  return compId;
}

void* EcsAddComponent(EcsWorld *world, EcsID entity, EcsID component)
{
  if(component >= world->numOfComponents || !EcsIsEntitiyAlive(world, entity))
    return NULL;

  if(EcsHasComponent(world, entity, component))
    return EcsGetComponent(world, entity, component);

  world->entities[entity] |= world->components[component].mask;
  world->components[component].data[entity] = calloc(1, world->components[component].size);
  return world->components[component].data[entity];
}

int EcsHasComponent(EcsWorld *world, EcsID entity, EcsID component)
{
  if(component >= world->numOfComponents || !EcsIsEntitiyAlive(world, entity))
    return 0;

  return world->entities[entity] & world->components[component].mask;
}

void* EcsGetComponent(EcsWorld *world, EcsID entity, EcsID component)
{
  if(component >= world->numOfComponents || !EcsIsEntitiyAlive(world, entity))
    return NULL;

  if(!EcsHasComponent(world, entity, component))
    return NULL;

  return world->components[component].data[entity];
}

void EcsRemoveComponent(EcsWorld *world, EcsID entity, EcsID component)
{
  if(component >= world->numOfComponents || !EcsIsEntitiyAlive(world, entity))
    return;

  if(!EcsHasComponent(world, entity, component))
    return;

  free(world->components[component].data[entity]);
  world->entities[entity] &= ~world->components[component].mask;
}

EcsID EcsRegisterSystem(EcsWorld *world, EcsCallback callback)
{
  EcsID sysId = world->numOfSystems;
  world->systems[world->numOfSystems].callback = callback;
  world->numOfSystems++;
  return sysId;
}

void EcsRequireComponent(EcsWorld *world, EcsID system, EcsID component)
{
  if(system >= world->numOfSystems || component >= world->numOfComponents)
    return;

  world->systems[system].requiredComponents |= world->components[component].mask;
}

void EcsUpdateSystem(EcsWorld *world, EcsID system, float dt)
{
  if(system >= world->numOfSystems)
    return;

  EcsID *entities = calloc(ECS_MAX_ENTITIES, sizeof(EcsID));
  unsigned long long j = 0;
  unsigned long long mask = (world->systems[system].requiredComponents | IS_ALIVE_BIT);
  for(int i = 0; i < ECS_MAX_ENTITIES; i++)
  {
    if((world->entities[i] & mask) == mask)
    {
      entities[j++] = i;
    }
  }

  world->systems[system].callback(world, entities, j, dt);
  free(entities);
}
