#ifndef ASSETS_LIBRARY_H
#define ASSETS_LIBRARY_H

#include "../shader/shader.h"
#include "../texture/texture.h"
#include "../sprite/sprite.h"
#include "../tileset/tileset.h"
#include "../tilemap/tilemap.h"
#include "../character/character.h"
#include "../scene/scene.h"

void InitAssetsLibrary(void);

void SaveShader(Shader shader, const char *name);
void SaveTexture2D(Texture2D texture, const char *name);
void SaveSprite(Sprite sprite, const char *name);
void SaveTileset(Tileset tileset, const char *name);
void SaveTilemap(Tilemap map, const char *name);
void SaveFont(Font font, const char *name);
void SaveScene(Scene scene, const char *name);

Shader* GetShader(const char *name);
Texture2D* GetTexture2D(const char *name);
Sprite* GetSprite(const char *name);
Tileset* GetTileset(const char *name);
Tilemap* GetTilemap(const char *name);
Font* GetFont(const char *name);
Scene* GetScene(const char *name);

void DisposeAssets();

#endif
