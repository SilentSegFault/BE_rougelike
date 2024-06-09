#include "assets_loader.h"
#include "assets_library.h"
#include "cJSON/cJSON.h"
#include "fonts_management.h"
#include "shader_management.h"
#include "texture_management.h"
#include "sprite_management.h"
#include "tileset_management.h"
#include "tilemap_management.h"
#include "scene_management.h"
#include "spritesheet_management.h"
#include "animation_management.h"
#include "../utility/loadFileSource.h"
#include <minwindef.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdio.h>
#include "../logger/logger.h"

const char *pathToAssetsDir;

void SetPathToDir(const char *path, void (*setter)(const char*))
{
  char *pathPtr = calloc(strlen(path) + 1, sizeof(char));
  strcpy(pathPtr, path);
  setter(pathPtr);
}

void SetAssetsDirPath(const char *path)
{
  pathToAssetsDir = path;
}

void InitAssetsLoader(const char *path)
{
  char pathBuffer[MAX_PATH];

  //Assets
  SetPathToDir(path, SetAssetsDirPath);

  //Shaders
  sprintf_s(pathBuffer, MAX_PATH, "%s/shaders", path);
  SetPathToDir(pathBuffer, SetShadersDirPath);

  //Textures
  sprintf_s(pathBuffer, MAX_PATH, "%s/textures", path);
  SetPathToDir(pathBuffer, SetTexturesDirPath);

  //Sprites
  sprintf_s(pathBuffer, MAX_PATH, "%s/sprites", path);
  SetPathToDir(pathBuffer, SetSpritesDirPath);

  //Tilesets
  sprintf_s(pathBuffer, MAX_PATH, "%s/tilesets", path);
  SetPathToDir(pathBuffer, SetTilesetDirPath);

  //Tilemaps
  sprintf_s(pathBuffer, MAX_PATH, "%s/tilemaps", path);
  SetPathToDir(pathBuffer, SetTilemapsDirPath);

  //Fonts
  sprintf_s(pathBuffer, MAX_PATH, "%s/fonts", path);
  SetPathToDir(pathBuffer, SetFontsDirPath);

  //Scenes
  sprintf_s(pathBuffer, MAX_PATH, "%s/scenes", path);
  SetPathToDir(pathBuffer, SetScenesDirPath);

  //Spritesheets
  sprintf_s(pathBuffer, MAX_PATH, "%s/spritesheets", path);
  SetPathToDir(pathBuffer, SetSpritesheetsDirPath);
  //Animations
  sprintf_s(pathBuffer, MAX_PATH, "%s/animations", path);
  SetPathToDir(pathBuffer, SetAnimationsDirPath);
}

void LoadShadersFromJson(cJSON *shadersLoadJson)
{
  cJSON *shaders = cJSON_GetObjectItemCaseSensitive(shadersLoadJson, "load");
  cJSON *shader = NULL;

  cJSON_ArrayForEach(shader, shaders)
  {
    cJSON *name = cJSON_GetObjectItemCaseSensitive(shader, "name");
    if(!cJSON_IsString(name))
    {
      LogWarning("Failed loading shader: name should be a string!");
    }

    Shader loadedShader;
    if(LoadShaderFromJson(shader, &loadedShader))
    {
      SaveShader(loadedShader, name->valuestring);
    }
    else
    {
      LogTagError("AssetsLoading", "Failed loading shader: `%s`", name->valuestring);
    }

  }
}

void LoadTexturesFromJson(cJSON *texturesLoadJson)
{
  cJSON *textures = cJSON_GetObjectItemCaseSensitive(texturesLoadJson, "load");
  cJSON *texture = NULL;

  cJSON_ArrayForEach(texture, textures)
  {
    cJSON *name = cJSON_GetObjectItemCaseSensitive(texture, "name");
    if(!cJSON_IsString(name))
    {
      LogWarning("Failed loading texture: name should be a string!");
    }
    Texture2D loadedTexture;
    if(LoadTextureFromJson(texture, &loadedTexture))
    {
      SaveTexture2D(loadedTexture, name->valuestring);
    }
    else
    {
      LogTagError("AssetsLoading", "Failed loading texture: `%s`", name->valuestring);
    }

  }
}

void LoadSpritesFromJson(cJSON *spritesLoadJson)
{
  cJSON *sprites = cJSON_GetObjectItemCaseSensitive(spritesLoadJson, "load");
  cJSON *sprite = NULL;

  cJSON_ArrayForEach(sprite, sprites)
  {
    cJSON *name = cJSON_GetObjectItemCaseSensitive(sprite, "name");
    if(!cJSON_IsString(name))
    {
      LogTagError("AssetsLoading", "Failed loading sprite: name should be a string!");
    }
    Sprite loadedSprite;
    if(LoadSpriteFromJson(sprite, &loadedSprite))
    {
      SaveSprite(loadedSprite, name->valuestring);
    }
    else
    {
      LogTagError("AssetsLoading", "Failed loading sprite: `%s`", name->valuestring);
    }
  }
}

void LoadTilesetsFromJson(cJSON *tilesetsLoadJson)
{
  cJSON *tilesets = cJSON_GetObjectItemCaseSensitive(tilesetsLoadJson, "load");
  cJSON *tileset = NULL;

  cJSON_ArrayForEach(tileset, tilesets)
  {
    cJSON *name = cJSON_GetObjectItemCaseSensitive(tileset, "name");
    if(!cJSON_IsString(name))
    {
      LogTagError("AssetsLoading", "Failed loading tileset: name should be a string!");
    }
    Tileset loadedTileset;
    if(LoadTilesetFromJson(tileset, &loadedTileset))
    {
      SaveTileset(loadedTileset, name->valuestring);
    }
    else
    {
      LogTagError("AssetsLoading", "Failed loading tileset: `%s`", name->valuestring);
    }
  }
}

void LoadTilemapsFromJson(cJSON *tilemapsLoadJson)
{
  cJSON *tilemaps = cJSON_GetObjectItemCaseSensitive(tilemapsLoadJson, "load");
  cJSON *tilemap = NULL;

  cJSON_ArrayForEach(tilemap, tilemaps)
  {
    cJSON *name = cJSON_GetObjectItemCaseSensitive(tilemap, "name");
    cJSON *source = cJSON_GetObjectItemCaseSensitive(tilemap, "source");
    if(!cJSON_IsString(name))
    {
      LogTagError("AssetsLoading", "Failed loading Tilemap: `name` should be a string!");
    }

    if(!cJSON_IsString(source))
    {
      LogTagError("AssetsLoading", "Failed loading Tilemap: `source` should be a string!");
    }

    char sourceBuf[MAX_PATH];
    sprintf_s(sourceBuf, MAX_PATH, "%s/%s", pathToTilemapsDir, source->valuestring);
    char *tilemapSource = LoadFileSource(sourceBuf);
    if(tilemapSource == NULL)
    {
      LogTagError("AssetsLoading", "Failed loading Tilemap: source path is invalid");
      continue;
    }

    cJSON *sourceJson = cJSON_Parse(tilemapSource);
    cJSON *tilemapSourceJson = cJSON_GetObjectItemCaseSensitive(sourceJson, "tilemap");

    if(!cJSON_IsObject(tilemapSourceJson))
    {
      LogTagError("AssetsLoading", "Failed loading Tilemap `%s`: specify tilemap object in source file", name->valuestring);
      continue;
    }

    Tilemap loadedMap;
    if(LoadTilemapFromJson(tilemapSourceJson, &loadedMap))
    {
      SaveTilemap(loadedMap, name->valuestring);
    }
    else
    {
      LogTagError("AssetsLoading", "Failed loading tilemap `%s`", name->valuestring);
    }
  }
}

void LoadFontsFromJson(cJSON *fontsLoadJson)
{
  cJSON *fonts = cJSON_GetObjectItemCaseSensitive(fontsLoadJson, "load");
  cJSON *font = NULL;

  cJSON_ArrayForEach(font, fonts)
  {
    cJSON *name = cJSON_GetObjectItemCaseSensitive(font, "name");
    if(!cJSON_IsString(name))
    {
      LogTagError("AssetsLoading", "Failed loading font: name should be a string!");
      continue;
    }
    Font loadedFont;
    if(LoadFontFromJson(font, &loadedFont))
    {
      SaveFont(loadedFont, name->valuestring);
    }
    else
    {
      LogTagError("AssetsLoading", "Failed loading font: `%s`", name->valuestring);
    }
  }
}

void LoadScenesFromJson(cJSON *scenesLoadJson)
{
  cJSON *scenes = cJSON_GetObjectItemCaseSensitive(scenesLoadJson, "load");
  cJSON *scene = NULL;

  cJSON_ArrayForEach(scene, scenes)
  {
    cJSON *name = cJSON_GetObjectItemCaseSensitive(scene, "name");
    if(!cJSON_IsString(name))
    {
      LogTagError("AssetsLoading", "Failed loading scene: name should be a string!");
    }

    Scene loadedScene;
    if(LoadSceneFromJson(scene, &loadedScene))
    {
      SaveScene(loadedScene, name->valuestring);
    }
    else
    {
      LogTagError("AssetsLoading", "Failed loading scene: `%s`", name->valuestring);
    }
  }
}

void LoadSpritesheetsFromJson(cJSON *spritesheetsLoadJson)
{
  cJSON *spritesheets = cJSON_GetObjectItemCaseSensitive(spritesheetsLoadJson, "load");
  cJSON *spritesheet = NULL;

  cJSON_ArrayForEach(spritesheet, spritesheets)
  {
    cJSON *name = cJSON_GetObjectItemCaseSensitive(spritesheet, "name");
    if(!cJSON_IsString(name))
    {
      LogTagError("AssetsLoading", "Failed loading spritesheet: name should be a string!");
    }

    Spritesheet loadedSpritesheet;
    if(LoadSpritesheetFromJson(spritesheet, &loadedSpritesheet))
    {
      SaveSpritesheet(loadedSpritesheet, name->valuestring);
    }
    else
    {
      LogTagError("AssetsLoading", "Failed loading spritesheet: `%s`", name->valuestring);
    }
  }
}

void LoadAnimationsFromJson(cJSON *animationsLoadJson)
{
  cJSON *animations = cJSON_GetObjectItemCaseSensitive(animationsLoadJson, "load");
  cJSON *animation = NULL;

  cJSON_ArrayForEach(animation, animations)
  {
    cJSON *name = cJSON_GetObjectItemCaseSensitive(animation, "name");
    if(!cJSON_IsString(name))
    {
      LogTagError("AssetsLoading", "Failed loading animation: name should be a string!");
    }

    Animation loadedAnimation;
    if(LoadAnimationFromJson(animation, &loadedAnimation))
    {
      SaveAnimation(loadedAnimation, name->valuestring);
    }
    else
    {
      LogTagError("AssetsLoading", "Failed loading animation: `%s`", name->valuestring);
    }
  }
}

void LoadAssetsFromJson(const char *pathToLoadFileDir, void(*loadFunction)(cJSON*))
{
  char loadFilePath[MAX_PATH];
  char *loadFileSource = NULL;
  cJSON *loadFileJson = NULL;

  sprintf_s(loadFilePath, MAX_PATH, "%s/load.json", pathToLoadFileDir);
  loadFileSource = LoadFileSource(loadFilePath);
  loadFileJson = cJSON_Parse(loadFileSource);
  loadFunction(loadFileJson);
  free(loadFileSource);
  cJSON_Delete(loadFileJson);
}
void LoadAssets()
{
  char loadFilePath[MAX_PATH];
  char *loadFileSource = NULL;
  cJSON *loadFileJson = NULL;

  LoadAssetsFromJson(pathToShadersDir, LoadShadersFromJson);
  LoadAssetsFromJson(pathToTexturesDir, LoadTexturesFromJson);
  LoadAssetsFromJson(pathToSpritesDir, LoadSpritesFromJson);
  LoadAssetsFromJson(pathToTilesetsDir, LoadTilesetsFromJson);
  LoadAssetsFromJson(pathToTilemapsDir, LoadTilemapsFromJson);
  LoadAssetsFromJson(pathToFontsDir, LoadFontsFromJson);
  LoadAssetsFromJson(pathToScenesDir, LoadScenesFromJson);
  LoadAssetsFromJson(pathToSpritesheetsDir, LoadSpritesheetsFromJson);
  LoadAssetsFromJson(pathToAnimationsDir, LoadAnimationsFromJson);
}
