#include "rand.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void InitRand()
{
  unsigned int seed = GetCurrentProcessId() * time(NULL);
  srand(seed);
}

int Randi(int min, int max)
{
  return rand() % (max + 1 - min) + min;
}

float Randf(float min, float max)
{
  return ((float)rand() / (float)RAND_MAX) * (max - min) + min;
}

double Rand(double min, double max)
{
  return ((double)rand() / (double)RAND_MAX) * (max - min) + min;
}
