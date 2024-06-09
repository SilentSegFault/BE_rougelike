#include "rendering_sprites.h"
#include "cglm/cglm.h"
#include "glad/glad.h"
#include <minwindef.h>
#include "../resource_management/assets_library.h"

static unsigned int rendererVAO;
static unsigned int frameVAO, frameVBO;
void InitSpriteRenderer()
{
  unsigned int VBO;

  float vertices[] =
  {
    //pos       //tex
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f
  };

  glGenVertexArrays(1, &rendererVAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(rendererVAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glGenVertexArrays(1, &frameVAO);
  glGenBuffers(1, &frameVBO);
  glBindVertexArray(frameVAO);
  glBindBuffer(GL_ARRAY_BUFFER, frameVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

}

void DrawSprite(Sprite *sprite, mat4 *projection, int layer, vec2 position, vec2 size, float rotation, int flipX, int flipY)
{
  mat4 model = GLM_MAT4_IDENTITY_INIT;

  glm_translate(model, (vec3){position[0], position[1], 0.0f});

  glm_rotate_at(model, (vec3){0.5f * size[0], 0.5f * size[1], 0.0f}, rotation, (vec3){0.0f, 0.0f, 1.0f});

  glm_scale(model, (vec3){size[0], size[1], 1.0f});

  ShaderSetMat4(sprite->shader, "model", model, TRUE);
  ShaderSetVector3(sprite->shader, "spriteColor", sprite->colorMask, FALSE);
  ShaderSetMat4(sprite->shader, "projection", *projection, FALSE);
  ShaderSetInteger(sprite->shader, "flipX", flipX, FALSE);
  ShaderSetInteger(sprite->shader, "flipY", flipY, FALSE);
  ShaderSetInteger(sprite->shader, "layer", layer, FALSE);

  glActiveTexture(GL_TEXTURE0);
  BindTexture(sprite->texture);

  glBindVertexArray(rendererVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

void DrawSpritesheetFrame(Spritesheet *spritesheet, mat4 *projection, int layer, int row, int frame, vec2 position, vec2 size, float rotation, int flip)
{
  Shader shader = *GetShader("spritesheet");
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(frameVAO);
  
  mat4 model = GLM_MAT4_IDENTITY_INIT;
  glm_translate(model, (vec3){position[0], position[1], 0.0f});
  glm_rotate_at(model, (vec3){0.5f * size[0], 0.5f * size[1], 0.0f}, rotation, (vec3){0.0f, 0.0f, 1.0f});
  glm_scale(model, (vec3){size[0], size[1], 1.0f});

  float x = (float)frame / spritesheet->cols;
  float y = (float)row / spritesheet->rows;
  float width = 1.0f / spritesheet->cols;
  float height = 1.0f / spritesheet->rows;

  if(flip)
  {
    x += width;
    width = -width;
  }

  float vertices[] =
  {
    //pos       //tex
    0.0f, 1.0f, x, y + height,
    1.0f, 0.0f, x + width, y,
    0.0f, 0.0f, x, y,
    0.0f, 1.0f, x, y + height,
    1.0f, 1.0f, x + width, y + height,
    1.0f, 0.0f, x + width, y
  };

  ShaderSetMat4(shader, "model", model, TRUE);
  ShaderSetMat4(shader, "projection", *projection, FALSE);
  ShaderSetInteger(shader, "layer", layer, FALSE);

  glBindTexture(GL_TEXTURE_2D, spritesheet->texture);

  glBindBuffer(GL_ARRAY_BUFFER, frameVBO);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void DisposeSpriteRenderer()
{
  glDeleteVertexArrays(1, &rendererVAO);
  glDeleteVertexArrays(1, &frameVBO);
  glDeleteBuffers(1, &frameVBO);
}
