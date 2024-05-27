#include "timer.h"
#include <time.h>

static clock_t timerStart;

void StartTimer()
{
  timerStart = clock();
}

long StopTimerMs()
{
  return 1000 * (double)(clock() - timerStart) / CLOCKS_PER_SEC;
}

float StopTimerSec()
{
  return  (float)(clock() - timerStart) / CLOCKS_PER_SEC;
}
