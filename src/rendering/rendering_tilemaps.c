#include "rendering_tilemaps.h"
#include "glad/glad.h"

void DrawTilemap(Tilemap *map, Shader *shader, mat4 *projection, vec2 position, vec2 size, float rotation)
{
  mat4 model = GLM_MAT4_IDENTITY_INIT;

  glm_translate(model, (vec3){position[0], position[1], 0.0f});

  glm_rotate_at(model, (vec3){0.5f * size[0], 0.5f * size[1], 0.0f}, rotation, (vec3){0.0f, 0.0f, 1.0f});

  glm_scale(model, (vec3){size[0] / map->width, size[1] / map->height, 1.0f});

  ShaderSetMat4(*shader, "model", model, TRUE);
  ShaderSetMat4(*shader, "projection", *projection, FALSE);

  for(int i = 0; i < map->layersCount; i++)
  {
    ShaderSetInteger(*shader, "layer", map->layers[i].drawLayer, FALSE);

    glActiveTexture(GL_TEXTURE0);
    BindTexture(map->layers[i].tilesetTexture);

    glBindVertexArray(map->layers[i].layerVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6 * map->width * map->height);
  }
  glBindVertexArray(0);
}
