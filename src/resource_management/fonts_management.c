#include "fonts_management.h"
#include "cJSON/cJSON.h"
#include "freetype/freetype.h"
#include "stb/stb_ds.h"
#include <minwindef.h>
#include <stdio.h>
#include <windows.h>
#include "../logger/logger.h"

const char *pathToFontsDir;

void SetFontsDirPath(const char *path)
{
  pathToFontsDir = path;
}

int LoadFont(const char *fontPath, int baseHeight, Font *loadedFont)
{
  FT_Library ft;
  if(FT_Init_FreeType(&ft))
  {
    LogTagError("FontLoading", "Failed initializing freetype");
    return 0;
  }

  FT_Face font;
  if(FT_New_Face(ft, fontPath, 0, &font))
  {
    FT_Done_FreeType(ft);
    LogTagError("FontLoading", "Failed initializing fontface");
    return 0;
  }

  FT_Set_Pixel_Sizes(font, 0, baseHeight);

  for(unsigned char c = 0; c < 128; c++)
  {
    Character createdChar;
    if(!CreateCharacter(font, c, &createdChar))
    {
      LogTagError("FontLoading", "Failed creating character: `%c`", c);
      continue;
    }

    loadedFont->characters[c] = createdChar;

  }

  FT_Done_Face(font);
  FT_Done_FreeType(ft);

  return 1;

}

int LoadFontFromJson(cJSON *font, Font *loadedFont)
{
  cJSON *source = cJSON_GetObjectItemCaseSensitive(font, "source");
  cJSON *baseHeight = cJSON_GetObjectItemCaseSensitive(font, "baseHeight");

  if(!cJSON_IsString(source))
  {
    LogTagError("FontLoading", "Failed loading font: `source` should be a string");
    return 0;
  }

  if(!cJSON_IsNumber(baseHeight))
  {
    LogTagError("FontLoading", "Failed loading font: `baseHeight` should be a number");
    return 0;
  }

  char fontPath[MAX_PATH];
  sprintf_s(fontPath, MAX_PATH, "%s/%s", pathToFontsDir, source->valuestring);

  if(!LoadFont(fontPath, baseHeight->valueint, loadedFont))
  {
    return 0;
  }

  return 1;
}


