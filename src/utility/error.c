#include "error.h"
#include <windows.h>

void FatalError(const char *message)
{
  MessageBoxA(NULL, message, "Error!", MB_OK | MB_ICONERROR);
  exit(EXIT_FAILURE);
}
