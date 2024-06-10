#ifndef COMPONENTS_UTIL_H
#define COMPONENTS_UTIL_H

#include "components.h"
#include "ecs.h"

void Translate(EcsWorld *world, Transform *transform, float dx, float dy);
void TranslateTo(EcsWorld *world, Transform *transform, float x, float y);
void Scale(EcsWorld *world, Transform *transform, float scale);
void Rotate(EcsWorld *world, Transform *transform, float angle);

void AddTransformChild(Transform *transform, EcsID child);
void SetTransformParent(Transform *tranform, EcsID parent);
void SetEntitiesTranformRelationship(EcsWorld *world, EcsID child, EcsID parent);

int AreColliding(EcsWorld *world, EcsID e1, EcsID e2);
void SetAnimation(EcsWorld *world, EcsID e, const char *animationName, BOOL flip, BOOL playOnce);
int AnimationFinished(EcsWorld *world, EcsID e);

#endif
