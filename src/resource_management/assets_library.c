#include "assets_library.h"
#include "stb/stb_ds.h"
#include "glad/glad.h"
#include "../logger/logger.h"
#include <stdlib.h>

static struct {char *key; Shader *value;} *shaders = NULL;
static struct {char *key; Texture2D *value;} *textures = NULL;
static struct {char *key; Sprite *value;} *sprites = NULL;
static struct {char *key; Tileset *value;} *tilesets = NULL;
static struct {char *key; Tilemap *value;} *tilemaps = NULL;
static struct {char *key; Font *value;} *fonts = NULL;
static struct {char *key; Scene *value;} *scenes = NULL;

void InitAssetsLibrary(void)
{
  sh_new_arena(shaders);
  sh_new_arena(textures);
  sh_new_arena(sprites);
  sh_new_arena(tilesets);
  sh_new_arena(tilemaps);
  sh_new_arena(fonts);
  sh_new_arena(scenes);
}

void SaveShader(Shader shader, const char *name)
{
  int i = shgeti(shaders, name);
  if(i >= 0)
  {
    LogWarning("Couldn't save duplicate. Shader with name `%s` already exists.", name);
    return;
  }

  Shader *shaderPtr = malloc(sizeof(Shader));
  if(shaderPtr == NULL)
  {
    LogWarning("Couldn't allocate memory for `%s` shader.", name);
    return;
  }

  *shaderPtr = shader;
  shput(shaders, name, shaderPtr);
}

void SaveTexture2D(Texture2D texture, const char *name)
{
  int i = shgeti(textures, name);
  if(i >= 0)
  {
    LogWarning("Couldn't save duplicate. Texture with name `%s` already exists.", name);
    return;
  }


  Texture2D *texturePtr = calloc(1, sizeof(Texture2D));
  if(texturePtr == NULL)
  {
    LogWarning("Couldn't allocate memory for `%s` texture.", name);
    return;
  }

  *texturePtr = texture;
  shput(textures, name, texturePtr);
}

void SaveSprite(Sprite sprite, const char *name)
{
  int i = shgeti(sprites, name);
  if(i >= 0)
  {
    LogWarning("Couldn't save duplicate. Sprite with name `%s` already exists.", name);
    return;
  }

  Sprite *spritePtr = malloc(sizeof(Sprite));
  if(spritePtr == NULL)
  {
    LogWarning("Couldn't allocate memory for `%s` sprite.", name);
    return;
  }

  *spritePtr = sprite;
  shput(sprites, name, spritePtr);

}

void SaveTileset(Tileset tileset, const char *name)
{
  int i = shgeti(tilesets, name);
  if(i >= 0)
  {
    LogWarning("Couldn't save duplicate. Tileset with name `%s` already exists.", name);
    return;
  }

  Tileset *tilesetPtr = malloc(sizeof(Tileset));
  if(tilesetPtr == NULL)
  {
    LogWarning("Couldn't allocate memory for `%s` tileset.", name);
    return;
  }

  *tilesetPtr = tileset;
  shput(tilesets, name, tilesetPtr);

}

void SaveTilemap(Tilemap tilemap, const char *name)
{
  int i = shgeti(tilemaps, name);
  if(i >= 0)
  {
    LogWarning("Couldn't save duplicate. Map with name `%s` already exists.", name);
    return;
  }

  Tilemap *mapPtr = malloc(sizeof(Tilemap));
  if(mapPtr == NULL)
  {
    LogWarning("Couldn't allocate memory for `%s` map.", name);
    return;
  }

  *mapPtr = tilemap;
  shput(tilemaps, name, mapPtr);

}

void SaveFont(Font font, const char *name)
{
  int i = shgeti(fonts, name);
  if(i >= 0)
  {
    LogWarning("Couldn't save duplicate. Font with name `%s` already exists.", name);
    return;
  }

  Font *fontPtr = malloc(sizeof(Font));
  if(fontPtr == NULL)
  {
    LogWarning("Couldn't allocate memory for `%s` font", name);
    return;
  }

  *fontPtr = font;
  shput(fonts, name, fontPtr);
}

void SaveScene(Scene scene, const char *name)
{
  int i = shgeti(scenes, name);
  if(i >= 0)
  {
    LogTagWarning("AssetsLibrary", "Couldn't save duplicate. Scene with name `%s` already exists.", name);
    return;
  }

  Scene *scenePtr = malloc(sizeof(Scene));
  if(scenePtr == NULL)
  {
    LogTagWarning("AssetsLibrary", "Couldn't allocate memory for `%s` scene", name);
    return;
  }

  *scenePtr = scene;
  shput(scenes, name, scenePtr);
}

Shader* GetShader(const char *name)
{
  int i = shgeti(shaders, name);

  if(i < 0)
  {
    LogWarning("Trying to get shader with name `%s` but it doesn't exists.", name);
    return shget(shaders, "default");
  }

  return shaders[i].value;
}

Texture2D* GetTexture2D(const char *name)
{
  int i = shgeti(textures, name);

  if(i < 0)
  {
    LogWarning("Trying to get texture with name `%s` but it doesn't exists.", name);
    return shget(textures, "default");
  }

  return textures[i].value;
}

Sprite* GetSprite(const char *name)
{
  int i = shgeti(sprites, name);

  if(i < 0)
  {
    LogWarning("Trying to get sprite with name `%s` but it doesn't exists.", name);
    return shget(sprites, "default");
  }

  return sprites[i].value;
}

Tileset* GetTileset(const char *name)
{
  int i = shgeti(tilesets, name);

  if(i < 0)
  {
    LogWarning("Trying to get tileset with name `%s` but it doesn't exists.", name);
    return shget(tilesets, "default");
  }

  return tilesets[i].value;
}

Tilemap* GetTilemap(const char *name)
{
  int i = shgeti(tilemaps, name);

  if(i < 0)
  {
    LogWarning("Trying to get map with name `%s` but it doesn't exists.", name);
    return shget(tilemaps, "default");
  }

  return tilemaps[i].value;
}

Font* GetFont(const char *name)
{
  int i = shgeti(fonts, name);

  if(i < 0)
  {
    LogWarning("Trying to get font with name `%s` but it doesn't exists.", name);
    return shget(fonts, "default");
  }

  return fonts[i].value;
}

Scene* GetScene(const char *name)
{
  int i = shgeti(scenes, name);

  if(i < 0)
  {
    LogTagWarning("AssetsLibrary", "Trying to get scene with name `%s` but it doesn't exists.", name);
    return shget(scenes, "default");
  }

  return scenes[i].value;
}

void DisposeTilemaps()
{
}

void DisposeTilesets()
{
}

void DisposeSprites()
{
}

void DisposeShaders()
{
  for(int i = 0; i < shlen(shaders); i++)
  {
    LogDebug("Deleting shader: %s", shaders[i].key);
    glDeleteProgram(*shaders[i].value);
  }
}

void DisposeTextures2D()
{
  for(int i = 0; i < shlen(textures); i++)
  {
    LogDebug("Deleting texture: %s", textures[i].key);
    glDeleteTextures(1, textures[i].value);
  }
}

void DisposeFonts()
{

}

void DisposeScenes()
{

}

void DisposeAssets()
{
  DisposeTilemaps();
  DisposeTilesets();
  DisposeSprites();
  DisposeShaders();
  DisposeTextures2D();
  DisposeFonts();
  DisposeScenes();
}
