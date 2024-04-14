/// @file
#ifndef RAND_H
#define RAND_H

/// @brief Initializes PRNG
void InitRand(void);
/// @brief Generates random integer in range.
///
/// @param[in] min Minimut returned value.
/// @param[in] max Maximum returned value.
/// @returns Generated random number.
int Randi(int min, int max);
/// @brief Generates random float in range.
///
/// @param[in] min Minimut returned value.
/// @param[in] max Maximum returned value.
/// @returns Generated random number.
float Randf(float min, float max);
/// @brief Generates random double in range.
///
/// @param[in] min Minimut returned value.
/// @param[in] max Maximum returned value.
/// @returns Generated random number.
double Rand(double min, double max);

#endif
