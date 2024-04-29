#ifndef RENDERING_TILEMAPS_H
#define RENDERING_TILEMAPS_H

#include "cglm/cglm.h"
#include "../map/map.h"
#include "../shader/shader.h"

void DrawTilemap(Map *map, Shader shader, vec2 position, vec2 size, float rotation, mat4 projection);

#endif
