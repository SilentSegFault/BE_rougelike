#include "resource_manager.h"
#include "stb/stb_ds.h"
#include "stb/stb_image.h"
#include "../utility/error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glad/glad.h"
#include <windows.h>
#include "pico_headers/pico_log.h"

static struct {char *key; Shader value;} *shaders = NULL;
static struct {char *key; Texture2D value;} *textures = NULL;

char* LoadShaderSource(const char *shaderFilePath)
{
  log_info("Loading shader source: %s", shaderFilePath);
  HANDLE hShaderFile = CreateFile(shaderFilePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);

  if(hShaderFile == INVALID_HANDLE_VALUE)
  {
    log_fatal("Failed to load file: %s", shaderFilePath);
    FATAL_ERROR();
  }

  DWORD dwFileSize = GetFileSize(hShaderFile, NULL);
  if(dwFileSize == 0xFFFFFFFF)
  {
    log_fatal("Failed to read size of file: %s", shaderFilePath);
    FATAL_ERROR();
  }

  char *source = malloc(dwFileSize + 1);
  if(source == NULL)
  {
    log_fatal("Failed to allocate memory for file: %s source.", shaderFilePath);
    FATAL_ERROR();
  }

  DWORD dwBytesRead;
  if(!ReadFile(hShaderFile, source, dwFileSize, &dwBytesRead, NULL))
  {
    log_fatal("Failed to read file: %s", shaderFilePath);
    FATAL_ERROR();
  }

  source[dwFileSize] = 0;

  log_debug("Shader source: %s loaded [%lu bytes].", shaderFilePath, dwFileSize);
  return source;
}

Shader LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, const char *name)
{
  log_info("Creating shader: %s", name);
  char *vertexSource = LoadShaderSource(vShaderFile);
  char *fragmentSource = LoadShaderSource(fShaderFile);
  char *geometrySource = NULL;

  if(gShaderFile != NULL)
    geometrySource = LoadShaderSource(gShaderFile);

  Shader shader = CompileShader(vertexSource, fragmentSource, geometrySource);
  free(vertexSource);
  free(fragmentSource);
  free(geometrySource);

  shput(shaders, name, shader);
  log_debug("Shader %s created.", name);
  return shader;
}

Shader GetShader(const char *name)
{
  return shget(shaders, name);
}

Texture2D LoadTexture(const char *file, int alpha, const char *name)
{
  log_info("Loading texture: %s.", name);
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

  log_debug("loading image data for %s.", name);
  int iNrChannels;
  unsigned char *data = stbi_load(file, &config.width, &config.height, &iNrChannels, 0);
  log_debug("Image data for %s loaded.", name);

  Texture2D texture = GenerateTexture(data, &config);
  
  stbi_image_free(data);

  shput(textures, name, texture);

  log_debug("Texture %s loaded.", name);
  return texture;
}

Texture2D GetTexture(const char *name)
{
  return shget(textures, name);
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
  DisposeShaders();
  DisposeTextures();
}
