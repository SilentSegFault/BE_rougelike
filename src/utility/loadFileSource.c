#include "loadFileSource.h"
#include "pico_headers/pico_log.h"
#include "error.h"

char* LoadFileSource(const char *path)
{
  log_trace("Loading file source: %s", path);
  HANDLE hShaderFile = CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);

  if(hShaderFile == INVALID_HANDLE_VALUE)
  {
    log_fatal("Failed to load file: %s", path);
    FATAL_ERROR();
  }

  DWORD dwFileSize = GetFileSize(hShaderFile, NULL);
  if(dwFileSize == 0xFFFFFFFF)
  {
    log_fatal("Failed to read size of file: %s", path);
    FATAL_ERROR();
  }

  char *source = malloc(dwFileSize + 1);
  if(source == NULL)
  {
    log_fatal("Failed to allocate memory for file: %s source.", path);
    FATAL_ERROR();
  }

  DWORD dwBytesRead;
  if(!ReadFile(hShaderFile, source, dwFileSize, &dwBytesRead, NULL))
  {
    log_fatal("Failed to read file: %s", path);
    FATAL_ERROR();
  }

  source[dwFileSize] = 0;

  log_trace("File source: %s loaded [%lu bytes].", path, dwFileSize);

  return source;
}
