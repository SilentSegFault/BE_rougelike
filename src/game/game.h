///@file
#ifndef GAME_H
#define GAME_H

#include <windows.h>

/// @brief Initializes required elements for game to run.
void InitGame(void);
/// @brief Updates one physics/systems step.
void Update(double deltaTime);
/// @brief Renders current frame.
void Render(HDC hdc);
/// @brief handles disposing resources allocated in InitGame(void).
void DisposeGame(void);

#endif
