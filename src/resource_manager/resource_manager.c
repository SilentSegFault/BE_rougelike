#include "resource_manager.h"
#include "stb/stb_ds.h"
#include "stb/stb_image.h"
#include "../utility/error.h"
#include "../utility/loadFileSource.h"
#include <minwindef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glad/glad.h"
#include <windows.h>
#include "pico_headers/pico_log.h"
#include "cJSON/cJSON.h"

static struct {char *key; Shader value;} *shaders = NULL;
static struct {char *key; Texture2D value;} *textures = NULL;
static struct {char *key; Tileset value;} *tilesets = NULL;
static struct {char *key; Map value;} *maps = NULL;
static char **keys = NULL;

Shader LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, const char *name)
{
  log_trace("Creating shader: %s", name);
  char *vertexSource = LoadFileSource(vShaderFile);
  char *fragmentSource = LoadFileSource(fShaderFile);
  char *geometrySource = NULL;

  if(gShaderFile != NULL)
    geometrySource = LoadFileSource(gShaderFile);

  Shader shader = CompileShader(vertexSource, fragmentSource, geometrySource);
  free(vertexSource);
  free(fragmentSource);
  free(geometrySource);

  char *nameLiteral = malloc(sizeof(char) * strlen(name) + 1);
  strcpy(nameLiteral, name);
  shput(shaders, nameLiteral, shader);
  return shader;
}

Shader GetShader(const char *name)
{
  return shget(shaders, name);
}

Texture2D LoadTexture(const char *file, int alpha, const char *name)
{
  log_trace("Loading texture: %s.", name);
  Texture2DConfig config = {0};

  config.width          = 0;
  config.height         = 0;
  config.internalFormat = GL_RGB;
  config.imageFormat    = GL_RGB;
  config.wrapS          = GL_REPEAT;
  config.wrapT          = GL_REPEAT;
  config.filterMin      = GL_LINEAR;
  config.filterMax      = GL_LINEAR;

  if(alpha)
  {
    config.internalFormat = GL_RGBA;
    config.imageFormat = GL_RGBA;
  }

  log_trace("loading image data for %s.", name);
  int iNrChannels;
  unsigned char *data = stbi_load(file, &config.width, &config.height, &iNrChannels, 0);
  log_trace("Image data for %s loaded.", name);

  Texture2D texture = GenerateTexture(data, &config);
  
  stbi_image_free(data);

  char *nameLiteral = malloc(sizeof(char) * strlen(name) + 1);
  strcpy(nameLiteral, name);
  shput(textures, nameLiteral, texture);

  log_trace("Texture %s loaded.", name);
  return texture;
}

Texture2D GetTexture(const char *name)
{
  return shget(textures, name);
}

Tileset LoadTileset(const char *file, int alpha, int tileWidth, int tileHeight, int spacing, int tileCount, int columns, const char *name)
{
  char textureName[255];
  sprintf_s(textureName, 255, "%sTex_", name);
  Tileset tileset = 
    {
      .texture = LoadTexture(file, alpha, textureName),
      .tileWidth = tileWidth,
      .tileHeight = tileHeight,
      .spacing = spacing,
      .tileCount = tileCount,
      .columns = columns
    };

  char *nameLiteral = malloc(sizeof(char) * strlen(name) + 1);
  strcpy(nameLiteral, name);
  shput(tilesets, nameLiteral, tileset);

  return tileset;
}

Tileset GetTileset(const char *name)
{
  return shget(tilesets, name);
}

MapLayer LoadMapLayer(int width, int height, Tileset tileset, int *tileData)
{
  unsigned int layerVBO;
  glGenBuffers(1, &layerVBO);

  int dataSize = width * height * 6 * 2 * 2;
  float vertexData[dataSize];

  float paddingX = 1.0f / (tileset.tileWidth * tileset.columns);
  float paddingY = 1.0f / (tileset.tileHeight * (tileset.tileCount / tileset.columns));

  int i = 0;
  for(int y = 0; y < height; y++)
  {
    for(int x = 0; x < width; x++)
    {
      int tile = tileData[x + y * width];
      float tx0 = (tile % tileset.columns) * (1.0f / tileset.columns) + paddingX;
      float ty0 = (tile / tileset.columns) * (1.0f / (tileset.tileCount / tileset.columns)) + paddingY;
      float txSize = (1.0f / tileset.columns) - paddingX * 2;
      float tySize = (1.0f / (tileset.tileCount / tileset.columns)) - paddingY * 2;

      // vertex 0 (top left)
      vertexData[i + 0] = x; // position x
      vertexData[i + 1] = y; // position y
      vertexData[i + 2] = tx0; // texcoord x
      vertexData[i + 3] = ty0; // texcoord y
      i += 4;

      // vertex 1 (top right)
      vertexData[i + 0] = x + 1; // position x
      vertexData[i + 1] = y; // position y
      vertexData[i + 2] = tx0 + txSize; // texcoord x
      vertexData[i + 3] = ty0; // texcoord y
      i += 4;

      // vertex 2 (bottom left)
      vertexData[i + 0] = x; // position x
      vertexData[i + 1] = y + 1; // position y
      vertexData[i + 2] = tx0; // texcoord x
      vertexData[i + 3] = ty0 + tySize; // texcoord y
      i += 4;

      // vertex 3 (top right)
      vertexData[i + 0] = x + 1; // position x
      vertexData[i + 1] = y; // position y
      vertexData[i + 2] = tx0 + txSize; // texcoord x
      vertexData[i + 3] = ty0; // texcoord y
      i += 4;

      // vertex 4 (bottom left)
      vertexData[i + 0] = x; // position x
      vertexData[i + 1] = y + 1; // position y
      vertexData[i + 2] = tx0; // texcoord x
      vertexData[i + 3] = ty0 + tySize; // texcoord y
      i += 4;

      // vertex 5 (bottom right)
      vertexData[i + 0] = x + 1; // position x
      vertexData[i + 1] = y + 1; // position y
      vertexData[i + 2] = tx0 + txSize; // texcoord x
      vertexData[i + 3] = ty0 + tySize; // texcoord y
      i += 4;
    }
  }


  unsigned int layerVAO;
  glGenVertexArrays(1, &layerVAO);
  glBindVertexArray(layerVAO);

  glBindBuffer(GL_ARRAY_BUFFER, layerVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(sizeof(float) * 2));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  MapLayer layer;
  layer.layerVAO = layerVAO;
  layer.tileset = tileset;

  return layer;
}

Map LoadMap(int width, int height, int layersCount, MapLayer *layers, const char *name)
{
  Map map;
  map.width = width;
  map.height = height;
  map.layersCount = layersCount;
  map.layers = layers;

  char *nameLiteral = malloc(sizeof(char) * strlen(name) + 1);
  strcpy(nameLiteral, name);
  shput(maps, nameLiteral, map);

  return map;
}

Map LoadMapFromFile(char *path, const char *name)
{
  char *mapFileSource = LoadFileSource(path);
  cJSON *mapJson = cJSON_Parse(mapFileSource);
  if(mapJson == NULL)
  {
    log_fatal("Failed loading textures load.json file.");
    FATAL_ERROR();
  }

  cJSON *map = cJSON_GetObjectItemCaseSensitive(mapJson, "map");

  cJSON *width = cJSON_GetObjectItemCaseSensitive(map, "width");
  cJSON *height = cJSON_GetObjectItemCaseSensitive(map, "height");
  cJSON *layers = cJSON_GetObjectItemCaseSensitive(map, "layers");

  if(!cJSON_IsNumber(width))
  {
    log_error("Error loading map from %s: wrong data format \"width\" should be a number!", path);
    return (Map){0};
  }
  
  if(!cJSON_IsNumber(height))
  {
    log_error("Error loading map from %s: wrong data format \"height\" should be a number!", path);
    return (Map){0};
  }

  if(!cJSON_IsArray(layers))
  {
    log_error("Error loading map from %s: wrong data format \"layers\" should be an array!", path);
    return (Map){0};
  }

  cJSON *layer = NULL;
  int currentLayer = 1;
  int numLayers = cJSON_GetArraySize(layers);

  MapLayer *mapLayers = malloc(sizeof(MapLayer) * numLayers);

  cJSON_ArrayForEach(layer, layers)
  {
    cJSON *tileset = cJSON_GetObjectItemCaseSensitive(layer, "tilesetName");
    cJSON *data = cJSON_GetObjectItemCaseSensitive(layer, "data");
    
    if(!cJSON_IsString(tileset))
    {
      log_error("Error loading map from %s in %i layer: wrong data format \"tileset\" should be a string!", path, currentLayer);
      return (Map){0};
    }

    if(!cJSON_IsArray(data))
    {
      log_error("Error loading map from %s in %i layer: wrong data format \"data\" should be an array!", path, currentLayer);
      return (Map){0};
    }

    int elements = cJSON_GetArraySize(data);
    cJSON *element = NULL;
    int tileData[elements];
    int currentElement = 0;
    cJSON_ArrayForEach(element, data)
    {
      if(!cJSON_IsNumber(element))
      {
        log_error("Error loading map from %s in %i layer: wrong data format, elements in \"data\" array should be numbers!", path, currentLayer);
        return (Map){0};
      }

      int num = element->valueint;
      tileData[currentElement++] = num;
    }

    Tileset layerTileset = GetTileset(tileset->valuestring);
    if(shgeti(tilesets, tileset->valuestring) < 0)
    {
      log_error("Error loading map from %s in %i layer: tileset '%s' doesn't exists!", path, currentLayer, tileset->valuestring);
      return (Map){0};
    }

    mapLayers[currentLayer - 1] = LoadMapLayer(width->valueint, height->valueint, layerTileset, tileData);
    log_debug("created layer vao: %i", mapLayers[currentLayer - 1].layerVAO);

    currentLayer++;
  }

  return LoadMap(width->valueint, height->valueint, numLayers, mapLayers, name);

  free(mapFileSource);
  cJSON_Delete(mapJson);
}

Map GetMap(const char *name)
{
  return shget(maps, name);
}

void LoadShaderAssets(char *pathToShadersDir)
{
  char shadersLoadFilePath[MAX_PATH];
  sprintf_s(shadersLoadFilePath, MAX_PATH, "%s/load.json", pathToShadersDir);
  char *shadersLoadFileSource = LoadFileSource(shadersLoadFilePath);
  cJSON *shadersJson = cJSON_Parse(shadersLoadFileSource);
  if(shadersJson == NULL)
  {
    log_fatal("Failed loading shaders load.json file.");
    FATAL_ERROR();
  }

  cJSON *shadersToLoad = cJSON_GetObjectItemCaseSensitive(shadersJson, "load");

  cJSON *shader = NULL;
  int current = 1;
  int all = cJSON_GetArraySize(shadersToLoad);
  cJSON_ArrayForEach(shader, shadersToLoad)
  {
    cJSON *name = cJSON_GetObjectItemCaseSensitive(shader, "name");
    cJSON *vertexSource = cJSON_GetObjectItemCaseSensitive(shader, "vertexSource");
    cJSON *fragmentSource = cJSON_GetObjectItemCaseSensitive(shader, "fragmentSource");
    cJSON *geometrySource = cJSON_GetObjectItemCaseSensitive(shader, "geometrySource");

    if(!cJSON_IsString(name))
    {
      log_error("Error loading shader [%i/%i]: wrong data format \"name\" should be a string!", current, all);
      continue;
    }

    if(!cJSON_IsString(vertexSource))
    {
      log_error("Error loading shader [%i/%i]: wrong data format \"vertexSource\" should be a string!", current, all);
      continue;
    }
    
    if(!cJSON_IsString(fragmentSource))
    {
      log_error("Error loading shader [%i/%i]: wrong data format \"fragmentSource\" should be a string!", current, all);
      continue;
    }

    char vShaderFile[MAX_PATH];
    char fShaderFile[MAX_PATH];
    char gShaderFile[MAX_PATH];

    sprintf_s(vShaderFile, MAX_PATH, "%s/%s", pathToShadersDir, vertexSource->valuestring);
    sprintf_s(fShaderFile, MAX_PATH, "%s/%s", pathToShadersDir, fragmentSource->valuestring);
    if(cJSON_IsString(geometrySource))
    {
      sprintf_s(gShaderFile, MAX_PATH, "%s/%s", pathToShadersDir, geometrySource->valuestring);
      LoadShader(vShaderFile, fShaderFile, gShaderFile, name->valuestring);
    }
    else
    {
      LoadShader(vShaderFile, fShaderFile, NULL, name->valuestring);
    }

    log_info("shader '%s' loaded [%i/%i]", name->valuestring, current, all);
    current++;
  }

  free(shadersLoadFileSource);
  cJSON_Delete(shadersJson);
}

void LoadTextureAssets(char *pathToTexturesDir)
{
  char texturesLoadFilePath[MAX_PATH];
  sprintf_s(texturesLoadFilePath, MAX_PATH, "%s/load.json", pathToTexturesDir);
  char *texturesLoadFileSource = LoadFileSource(texturesLoadFilePath);
  cJSON *texturesJson = cJSON_Parse(texturesLoadFileSource);
  if(texturesJson == NULL)
  {
    log_fatal("Failed loading textures load.json file.");
    FATAL_ERROR();
  }

  cJSON *texturesToLoad = cJSON_GetObjectItemCaseSensitive(texturesJson, "load");

  cJSON *texture = NULL;
  int current = 1;
  int all = cJSON_GetArraySize(texturesToLoad);
  cJSON_ArrayForEach(texture, texturesToLoad)
  {
    cJSON *name = cJSON_GetObjectItemCaseSensitive(texture, "name");
    cJSON *source = cJSON_GetObjectItemCaseSensitive(texture, "source");
    cJSON *alpha = cJSON_GetObjectItemCaseSensitive(texture, "alpha");

    if(!cJSON_IsString(name))
    {
      log_error("Error loading texture [%i/%i]: wrong data format \"name\" should be a string!", current, all);
      continue;
    }

    if(!cJSON_IsString(source))
    {
      log_error("Error loading texture [%i/%i]: wrong data format \"source\" should be a string!", current, all);
      continue;
    }
    
    if(!cJSON_IsBool(alpha))
    {
      log_error("Error loading texture [%i/%i]: wrong data format \"alpha\" should be a bool!", current, all);
      continue;
    }

    char sourceFilePath[MAX_PATH];
    sprintf_s(sourceFilePath, MAX_PATH, "%s/%s", pathToTexturesDir, source->valuestring);

    BOOL alphaValue = cJSON_IsTrue(alpha);

    LoadTexture(sourceFilePath, alphaValue, name->valuestring);

    log_info("texture '%s' loaded [%i/%i]", name->valuestring, current, all);
    current++;
  }

  free(texturesLoadFileSource);
  cJSON_Delete(texturesJson);
}

void LoadTilesetAssets(char *pathToTilesetsDir)
{
  char tilesetsLoadFilePath[MAX_PATH];
  sprintf_s(tilesetsLoadFilePath, MAX_PATH, "%s/load.json", pathToTilesetsDir);
  char *tilesetsLoadFileSource = LoadFileSource(tilesetsLoadFilePath);
  cJSON *tilesetsJson = cJSON_Parse(tilesetsLoadFileSource);
  if(tilesetsJson == NULL)
  {
    log_fatal("Failed loading tilesets load.json file.");
    FATAL_ERROR();
  }

  cJSON *tilesetsToLoad = cJSON_GetObjectItemCaseSensitive(tilesetsJson, "load");

  cJSON *tileset = NULL;
  int current = 1;
  int all = cJSON_GetArraySize(tilesetsToLoad);
  cJSON_ArrayForEach(tileset, tilesetsToLoad)
  {
    cJSON *name = cJSON_GetObjectItemCaseSensitive(tileset, "name");
    cJSON *source = cJSON_GetObjectItemCaseSensitive(tileset, "source");
    cJSON *alpha = cJSON_GetObjectItemCaseSensitive(tileset, "alpha");
    cJSON *tileWidth = cJSON_GetObjectItemCaseSensitive(tileset, "tileWidth");
    cJSON *tileHeight = cJSON_GetObjectItemCaseSensitive(tileset, "tileHeight");
    cJSON *spacing = cJSON_GetObjectItemCaseSensitive(tileset, "spacing");
    cJSON *tileCount = cJSON_GetObjectItemCaseSensitive(tileset, "tileCount");
    cJSON *columns = cJSON_GetObjectItemCaseSensitive(tileset, "columns");

    if(!cJSON_IsString(name))
    {
      log_error("Error loading tileset [%i/%i]: wrong data format \"name\" should be a string!", current, all);
      continue;
    }

    if(!cJSON_IsString(source))
    {
      log_error("Error loading tileset [%i/%i]: wrong data format \"source\" should be a string!", current, all);
      continue;
    }
    
    if(!cJSON_IsBool(alpha))
    {
      log_error("Error loading tileset [%i/%i]: wrong data format \"alpha\" should be a bool!", current, all);
      continue;
    }
    if(!cJSON_IsNumber(tileWidth))
    {
      log_error("Error loading tileset [%i/%i]: wrong data format \"tileWidth\" should be a number!", current, all);
      continue;
    }

    if(!cJSON_IsNumber(tileHeight))
    {
      log_error("Error loading tileset [%i/%i]: wrong data format \"tileHeight\" should be a number!", current, all);
      continue;
    }
    
    if(!cJSON_IsNumber(spacing))
    {
      log_error("Error loading tileset [%i/%i]: wrong data format \"spacing\" should be a number!", current, all);
      continue;
    
    }
    if(!cJSON_IsNumber(tileCount))
    {
      log_error("Error loading tileset [%i/%i]: wrong data format \"tileCount\" should be a number!", current, all);
      continue;
    }

    if(!cJSON_IsNumber(columns))
    {
      log_error("Error loading tileset [%i/%i]: wrong data format \"columns\" should be a number!", current, all);
      continue;
    }

    char sourceFilePath[MAX_PATH];
    sprintf_s(sourceFilePath, MAX_PATH, "%s/%s", pathToTilesetsDir, source->valuestring);
    BOOL alphaValue = cJSON_IsTrue(alpha);

    LoadTileset(sourceFilePath,
                alphaValue,
                tileWidth->valueint,
                tileHeight->valueint,
                spacing->valueint,
                tileCount->valueint,
                columns->valueint,
                name->valuestring);
    
    log_info("tileset '%s' loaded [%i/%i]", name->valuestring, current, all);
    current++;
  }

  free(tilesetsLoadFileSource);
  cJSON_Delete(tilesetsJson);

}



void LoadMapAssets(char *pathToMapsDir)
{
  char mapsLoadFilePath[MAX_PATH];
  sprintf_s(mapsLoadFilePath, MAX_PATH, "%s/load.json", pathToMapsDir);
  char *mapsLoadFileSource = LoadFileSource(mapsLoadFilePath);
  cJSON *mapsJson = cJSON_Parse(mapsLoadFileSource);
  if(mapsJson == NULL)
  {
    log_fatal("Failed loading textures load.json file.");
    FATAL_ERROR();
  }

  cJSON *mapsToLoad = cJSON_GetObjectItemCaseSensitive(mapsJson, "load");

  cJSON *map = NULL;
  int current = 1;
  int all = cJSON_GetArraySize(mapsToLoad);
  cJSON_ArrayForEach(map, mapsToLoad)
  {
    cJSON *name = cJSON_GetObjectItemCaseSensitive(map, "name");
    cJSON *source = cJSON_GetObjectItemCaseSensitive(map, "source");

    if(!cJSON_IsString(name))
    {
      log_error("Error loading map [%i/%i]: wrong data format \"name\" should be a string!", current, all);
      continue;
    }

    if(!cJSON_IsString(source))
    {
      log_error("Error loading map [%i/%i]: wrong data format \"source\" should be a string!", current, all);
      continue;
    }
    
    char sourceFilePath[MAX_PATH];
    sprintf_s(sourceFilePath, MAX_PATH, "%s/%s", pathToMapsDir, source->valuestring);

    LoadMapFromFile(sourceFilePath, name->valuestring);

    log_info("map '%s' loaded [%i/%i]", name->valuestring, current, all);
    current++;
  }

  free(mapsLoadFileSource);
  cJSON_Delete(mapsJson);
}

void LoadAssets(char *pathToAssetsDir)
{
  char dir[MAX_PATH];


  sprintf_s(dir, MAX_PATH, "%s/shaders", pathToAssetsDir);
  LoadShaderAssets(dir);

  sprintf_s(dir, MAX_PATH, "%s/textures", pathToAssetsDir);
  LoadTextureAssets(dir);

  sprintf_s(dir, MAX_PATH, "%s/tilesets", pathToAssetsDir);
  LoadTilesetAssets(dir);

  sprintf_s(dir, MAX_PATH, "%s/maps", pathToAssetsDir);
  LoadMapAssets(dir);
}

void DisposeShaders()
{
  for(int i = 0; i < shlen(shaders); i++)
  {
    log_debug("Deleting shader: %s", shaders[i].key);
    glDeleteProgram(shaders[i].value);
  }
}

void DisposeTextures()
{
  for(int i = 0; i < shlen(textures); i++)
  {
    log_debug("Deleting texture: %s", textures[i].key);
    glDeleteTextures(1, &textures[i].value);
  }
}

void DisposeResources()
{
  for(int i = 0; i < arrlen(keys); i++)
  {
    free(keys[i]);
  }
  arrfree(keys);
  DisposeShaders();
  DisposeTextures();
}
