#include "loadFileSource.h"
#include "error.h"
#include "../logger/logger.h"

char* LoadFileSource(const char *path)
{
  HANDLE hShaderFile = CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);

  if(hShaderFile == INVALID_HANDLE_VALUE)
  {
    LogError("Failed to load file: %s", path);
    return NULL;
  }

  DWORD dwFileSize = GetFileSize(hShaderFile, NULL);
  if(dwFileSize == 0xFFFFFFFF)
  {
    LogError("Failed to load file: %s", path);
    return NULL;
  }

  char *source = malloc(dwFileSize + 1);
  if(source == NULL)
  {
    LogError("Failed to allocate memory for file: %s source.", path);
    return NULL;
  }

  DWORD dwBytesRead;
  if(!ReadFile(hShaderFile, source, dwFileSize, &dwBytesRead, NULL))
  {
    LogError("Failed to load file: %s", path);
    return NULL;
  }

  source[dwFileSize] = 0;

  return source;
}
