#ifndef SCENE_MANAGEMENT_H
#define SCENE_MANAGEMENT_H

#include "../scene/scene.h"
#include "cJSON/cJSON.h"

extern const char *pathToScenesDir;

void SetScenesDirPath(const char *path);
int LoadSceneFromJson(cJSON *scene, Scene *loadedScene);

#endif
