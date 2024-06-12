#ifndef CHARACTER_H
#define CHARACTER_H

#include "cglm/types.h"
#include "ft2build.h"
#include FT_FREETYPE_H

typedef struct
{
  unsigned int texture;
  ivec2 size;
  ivec2 bearing;
  unsigned int advance;
} Character;

typedef struct
{
  Character characters[128];
} Font;

int CreateCharacter(FT_Face font, char c, Character *createdChar);

#endif
