#include "rendering_text.h"
#include "ft2build.h"
#include FT_FREETYPE_H
#include "glad/glad.h"
#include "stb/stb_ds.h"
#include "../logger/logger.h"

static unsigned int textVAO, textVBO;
void InitTextRenderer()
{
  glGenVertexArrays(1, &textVAO);
  glGenBuffers(1, &textVBO);
  glBindVertexArray(textVAO);
  glBindBuffer(GL_ARRAY_BUFFER, textVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void RenderText(Shader *shader, mat4 *projection, int layer, Font *font, const char *text, vec2 txtPosition, float scale, vec3 color)
{
  // activate corresponding render state	
  ShaderSetVector3(*shader, "textColor", color, TRUE);
  ShaderSetMat4(*shader, "projection", *projection, FALSE);
  ShaderSetInteger(*shader, "layer", layer, FALSE);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(textVAO);

  vec2 position = {txtPosition[0], txtPosition[1]};

  // iterate through all characters
  unsigned char c;
  while((c = *text))
  {
    Character ch = font->characters[c];

    float xpos = position[0] + ch.bearing[0] * scale;
    float ypos = position[1] - ch.bearing[1] * scale;

    float w = ch.size[0] * scale;
    float h = ch.size[1] * scale;
    // update VBO for each character
    float vertices[6][4] = {
      { xpos,     ypos + h,   0.0f, 1.0f },            
      { xpos,     ypos,       0.0f, 0.0f },
      { xpos + w, ypos,       1.0f, 0.0f },

      { xpos,     ypos + h,   0.0f, 1.0f },
      { xpos + w, ypos,       1.0f, 0.0f },
      { xpos + w, ypos + h,   1.0f, 1.0f }           
    };
    // render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, ch.texture);
    // update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, textVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
    position[0] += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    text++;
  }
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void DisposeTextRenderer()
{
  glDeleteVertexArrays(1, &textVAO);
  glDeleteBuffers(1, &textVBO);
}
