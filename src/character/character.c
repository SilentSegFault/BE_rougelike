#include "character.h"
#include "freetype/freetype.h"
#include "glad/glad.h"

int CreateCharacter(FT_Face font, char c, Character *createdChar)
{
  if(FT_Load_Char(font, c, FT_LOAD_RENDER))
  {
    return 0;
  }

  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    GL_RED,
    font->glyph->bitmap.width,
    font->glyph->bitmap.rows,
    0,
    GL_RED,
    GL_UNSIGNED_BYTE,
    font->glyph->bitmap.buffer
  );

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  Character ch;
  ch.texture = texture;
  ch.size[0] = font->glyph->bitmap.width;
  ch.size[1] = font->glyph->bitmap.rows;
  ch.bearing[0] = font->glyph->bitmap_left;
  ch.bearing[1] = font->glyph->bitmap_top;
  ch.advance = font->glyph->advance.x;

  *createdChar = ch;

  return 1;
}
