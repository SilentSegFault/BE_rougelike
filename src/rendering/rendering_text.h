#ifndef RENDERING_TEXT_H
#define RENDERING_TEXT_H

#include "cglm/types.h"
#include "../character/character.h"
#include "../shader/shader.h"

void InitTextRenderer();
void RenderText(Shader *shader, mat4 *projection, int layer, Font *font, const char *text, vec2 position, float scale, vec3 color);
void DisposeTextRenderer();

#endif
