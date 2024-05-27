#ifndef RENDERING_TILEMAPS_H
#define RENDERING_TILEMAPS_H

#include "cglm/cglm.h"
#include "../tilemap/tilemap.h"
#include "../shader/shader.h"

void DrawTilemap(Tilemap *map, Shader *shader, mat4 *projection, vec2 position, vec2 size, float rotation);

#endif
