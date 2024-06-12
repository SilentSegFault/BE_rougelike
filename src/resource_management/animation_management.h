#ifndef ANIMATION_MANAGEMENT_H
#define ANIMATION_MANAGEMENT_H

#include "../animation/animation.h"
#include "cJSON/cJSON.h"

extern const char *pathToAnimationsDir;

void SetAnimationsDirPath(const char *path);
int LoadAnimationFromJson(cJSON *sprite, Animation *loadedAnimation);

#endif
