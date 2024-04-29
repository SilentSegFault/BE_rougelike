#include "rendering_tilemaps.h"
#include "glad/glad.h"
#include "pico_headers/pico_log.h"

void DrawTilemap(Map *map, Shader shader, vec2 position, vec2 size, float rotation, mat4 projection)
{
  UseShader(shader);

  mat4 model = GLM_MAT4_IDENTITY_INIT;

  glm_translate(model, (vec3){position[0], position[1], 0.0f});

  glm_rotate_at(model, (vec3){0.5f * size[0], 0.5f * size[1], 0.0f}, rotation, (vec3){0.0f, 0.0f, 1.0f});

  glm_scale(model, (vec3){size[0] / map->width, size[1] / map->height, 1.0f});

  ShaderSetMat4(shader, "model", model);
  ShaderSetMat4(shader, "projection", projection);

  log_debug("layers: %i", map->layersCount);
  log_debug("texture: %i", map->layers[0].tileset.texture);
  log_debug("vao: %i", map->layers[0].layerVAO);
  for(int i = 0; i < map->layersCount; i++)
  {
    glActiveTexture(GL_TEXTURE0);
    BindTexture(map->layers[i].tileset.texture);

    glBindVertexArray(map->layers[i].layerVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6 * map->width * map->height);
  }
  glBindVertexArray(0);
}
