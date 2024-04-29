/// @file
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "../shader/shader.h"
#include "../texture/texture.h"
#include "../tileset/tileset.h"
#include "../map/map.h"

/// @brief Loads shader program into memory
///
/// Loads source files to memory, compiles and links them to create complete shader program.
///
/// @param vShaderFile Path to vertex shader source file.
/// @param fShaderFile Path to fragment shader source file.
/// @param gShaderFile _optional_ Path to geometry shader source file. Use NULL if won't be used.
/// @param name Name with which the Shader will be stored.
/// @returns Handle to compiled shader program.
Shader LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, const char *name);
/// @brief Retrieves Shader with specified name from loaded resources
///
/// @param name Shader name
/// @returns Handle to required shader or NULL.
Shader GetShader(const char *name);

/// @brief Loads texture from file into memory
///
/// Loads and configures texture according to @p alpha param
///
/// @param[in] file Path to texture file.
/// @param[in] alpha Determines if texture should be cofigured as RGBA (when set to TRUE/1) or RGB (when set to FALSE/0).
/// @param[in] name Name with which the texture will be saved.
/// @returns Handle to loaded texture.
Texture2D LoadTexture(const char *file, int alpha, const char *name);
/// @brief Retrieves Texture2D with specified name from loaded resources
///
/// @param name Texture2D name.
/// @returns Handle to required Texture2D or NULL.
Texture2D GetTexture(const char *name);

Tileset LoadTileset(const char *file, int alpha, int tileWidth, int tileHeight, int spacing, int tileCount, int columns, const char *name);

Tileset GetTileset(const char *name);

MapLayer LoadMapLayer(int width, int height, Tileset tileset, int *tileData);

Map LoadMap(int width, int height, int layersCount, MapLayer *layers, const char *name);

Map GetMap(const char *name);

void LoadAssets(char *pathToAssetsDir);

/// @brief Disposes all resources.
void DisposeResources();

#endif
