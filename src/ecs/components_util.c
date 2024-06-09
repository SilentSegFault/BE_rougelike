#include "components_util.h"
#include "cglm/cglm.h"
#include "../logger/logger.h"
#include "components.h"
#include "ecs.h"
#include "../resource_management/assets_library.h"

void Translate(EcsWorld *world, Transform *transform, float dx, float dy)
{
  transform->position[0] += dx;
  transform->position[1] += dy;

  for(int i = 0; i < transform->numOfChildren; i++)
  {
    Transform *childTransform = EcsGetComponent(world, transform->children[i], TransformComp);
    if(childTransform != NULL)
    {
      Translate(world, childTransform, dx, dy);
    }
  }
}

void TranslateTo(EcsWorld *world, Transform *transform, float x, float y)
{
  float x_translation = x - transform->position[0];
  float y_translation = y - transform->position[1];

  Translate(world, transform, x_translation, y_translation);
}

void Scale(EcsWorld *world, Transform *transform, float scale)
{
  transform->scale[0] *= scale;
  transform->scale[1] *= scale;

  for(int i = 0; i < transform->numOfChildren; i++)
  {
    Transform *childTransform = EcsGetComponent(world, transform->children[i], TransformComp);
    if(childTransform != NULL)
    {
      float dist = glm_vec2_distance(transform->position, childTransform->position);
      glm_vec2_adds(childTransform->position, dist * scale, childTransform->position);
      Scale(world, childTransform, scale);
    }
  }
}

void Rotate(EcsWorld *world, Transform *transform, float angle)
{
  transform->rotation += angle;

  for(int i = 0; i < transform->numOfChildren; i++)
  {
    Transform *childTransform = EcsGetComponent(world, transform->children[i], TransformComp);
    if(childTransform != NULL)
    {
      float x_rotated = ((childTransform->position[0] - transform->position[0]) * cos(angle))
                        - ((childTransform->position[1] - transform->position[1]) * sin(angle))
                        + transform->position[0];

      float y_rotated = ((childTransform->position[1] - transform->position[1]) * cos(angle))
                        + ((childTransform->position[0] - transform->position[0]) * sin(angle)) + transform->position[1];

      TranslateTo(world, childTransform, x_rotated, y_rotated);
      Rotate(world, childTransform, angle);
    }
  }
}

void AddTransformChild(Transform *transform, EcsID child)
{
  if(transform->children == NULL)
  {
    transform->children = malloc(sizeof(int));
  }
  else
  {
    EcsID *newChildren = realloc(transform->children, sizeof(EcsID) * transform->numOfChildren + 1);
    if(newChildren == NULL)
    {
      LogTagWarning("ComponentsUtil", "Couldn't allocate memory for new transform child.");
      return;
    }
    transform->children = newChildren;
  }

  transform->children[transform->numOfChildren] = child;
  transform->numOfChildren++;
}

void SetTransformParent(Transform *tranform, EcsID parent)
{
  tranform->parent = parent;
}

void SetEntitiesTranformRelationship(EcsWorld *world, EcsID child, EcsID parent)
{
  Transform *childTransform = EcsGetComponent(world, child, TransformComp);
  Transform *parentTransform = EcsGetComponent(world, parent, TransformComp);

  if(childTransform == NULL || parentTransform == NULL)
  {
    LogTagWarning("ComponentsUtil", "Couldn't set transform relationship, one of entities doesn't have transform component.");
    return;
  }

  AddTransformChild(parentTransform, child);
  SetTransformParent(childTransform, parent);
}

int AreColliding(EcsWorld *world, EcsID e1, EcsID e2)
{
  Collider *collider1 = EcsGetComponent(world, e1, ColliderComp);
  Collider *collider2 = EcsGetComponent(world, e2, ColliderComp);

  if(collider1->collisionLayer != collider2->collisionLayer)
  {
    return 0;
  }

  Transform *transform1 = EcsGetComponent(world, e1, TransformComp);
  Transform *transform2 = EcsGetComponent(world, e2, TransformComp);

  float w1 = collider1->width;
  float h1 = collider1->height;
  float x1 = transform1->position[0] - w1 * 0.5f + collider1->offsetX;
  float y1 = transform1->position[1] - h1 * 0.5f + collider1->offsetY;

  float w2 = collider2->width;
  float h2 = collider2->height;
  float x2 = transform2->position[0] - w2 * 0.5f + collider2->offsetX;
  float y2 = transform2->position[1] - h2 * 0.5f + collider2->offsetY;

  return x2 < (x1 + w1) && (x2 + w2) > x1 && y2 < (y1 + h1) && (y2 + h2) > y1;
}

void SetAnimation(EcsWorld *world, EcsID e, const char *animationName, BOOL flip)
{
  Animator *animator = EcsGetComponent(world, e, AnimatorComp);
  if(animator == NULL)
  {
    LogTagWarning("ComponentsUtil", "Couldn't set animation, entity doesn't have animator component.");
    return;
  }
  Animation *animation = GetAnimation(animationName);

  if(animator->currentAnimation == animation)
  {
    return;
  }

  animator->frameCounter = 0;
  animator->currentFrame = 0;
  animator->currentAnimation = animation;
  animator->flip = flip;
}
