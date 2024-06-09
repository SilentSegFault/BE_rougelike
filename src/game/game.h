#ifndef GAME_H
#define GAME_H

#include <windows.h>
#include "../scene/scene.h"

typedef struct
{
  unsigned long long gameTime;
  unsigned long long frameCount;
  Scene *currentScene;
} Game;

extern Game currentGame;

void InitGame(void);
void Update(double deltaTime);
void Render(void);
void DisposeGame(void);

void LoadScene(const char *sceneName);
Scene* GetCurrentScene();
void UnloadScene();

#endif
