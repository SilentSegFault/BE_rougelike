#ifndef RENDERING_DEBUG_H
#define RENDERING_DEBUG_H

#include "cglm/types.h"

void InitDebugRenderer();
void DrawRect(mat4 *projection, vec2 pos, vec2 size, float rotation, vec3 color);
void DisposeDebugRenderer();

#endif
