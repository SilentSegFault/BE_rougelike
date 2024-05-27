#include "logger.h"
#include <string.h>
#include <windows.h>
#include <stdio.h>
#include <stdarg.h>

static HANDLE hLogFile = NULL;

BOOL DirectoryExists(LPCTSTR szPath)
{
  DWORD dwAttrib = GetFileAttributes(szPath);

  return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
         (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

void InitLogger(const char *logsDirPath)
{
  SYSTEMTIME st;
  GetLocalTime(&st);

  char logsSubDirectory[24];
  sprintf(logsSubDirectory, "Logs_%02d_%02d_%04d", st.wDay, st.wMonth, st.wYear);

  char logsFile[16];
  sprintf(logsFile, "Log_%02d_%02d.log", st.wHour, st.wMinute);

  char pathToSubDirectory[MAX_PATH];
  sprintf(pathToSubDirectory, "%s/%s", logsDirPath, logsSubDirectory);

  if(!DirectoryExists(pathToSubDirectory))
    CreateDirectory(pathToSubDirectory, NULL);

  char logFilePath[MAX_PATH];
  sprintf(logFilePath, "%s/%s/%s", logsDirPath, logsSubDirectory, logsFile);

  hLogFile = CreateFile(logFilePath, FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL);
  if(hLogFile == INVALID_HANDLE_VALUE)
  {
    MessageBoxA(NULL, "Something wrong, i can feel it...", "ERROR!", MB_ICONERROR);
    exit(EXIT_FAILURE);
    return;
  }
}

void Log(const char *logLevel, const char *tag, const char *msg, va_list args)
{
  DWORD bufSize = 1024 * 3;
  char msgBuf[bufSize];

  SYSTEMTIME st;
  GetLocalTime(&st);

  vsprintf_s(msgBuf, bufSize, msg, args);
  char logBuf[bufSize];
  if(tag == NULL)
    sprintf_s(logBuf, bufSize, "[%02d:%02d:%02d.%04d] <%s> %s\n",st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, logLevel, msgBuf);
  else
    sprintf_s(logBuf, bufSize, "[%02d:%02d:%02d.%04d] <%s> [%s] %s\n",st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, logLevel, tag, msgBuf);

  DWORD bytesToWrite = strlen(logBuf);
  DWORD bytesWritten;

  WriteFile(hLogFile, logBuf, bytesToWrite, &bytesWritten, NULL);
  printf("%s", logBuf);
}

void LogTrace(const char *msg, ...)
{
  va_list args;
  va_start(args, msg);
  Log("TRACE", NULL, msg, args);
  va_end(args);
}

void LogDebug(const char *msg, ...)
{
  va_list args;
  va_start(args, msg);
  Log("DEBUG", NULL, msg, args);
  va_end(args);
}

void LogInfo(const char *msg, ...)
{
  va_list args;
  va_start(args, msg);
  Log("INFO", NULL, msg, args);
  va_end(args);
}

void LogWarning(const char *msg, ...)
{
  va_list args;
  va_start(args, msg);
  Log("WARNING", NULL, msg, args);
  va_end(args);
}

void LogError(const char *msg, ...)
{
  va_list args;
  va_start(args, msg);
  Log("ERROR", NULL, msg, args);
  va_end(args);
}

void LogFatal(const char *msg, ...)
{
  va_list args;
  va_start(args, msg);
  Log("FATRAL", NULL, msg, args);
  va_end(args);
}

void LogTagTrace(const char *tag, const char *msg, ...)
{
  va_list args;
  va_start(args, msg);
  Log("TRACE", tag, msg, args);
  va_end(args);
}

void LogTagDebug(const char *tag, const char *msg, ...)
{
  va_list args;
  va_start(args, msg);
  Log("DEBUG", tag, msg, args);
  va_end(args);
}

void LogTagInfo(const char *tag, const char *msg, ...)
{
  va_list args;
  va_start(args, msg);
  Log("INFO", tag, msg, args);
  va_end(args);
}

void LogTagWarning(const char *tag, const char *msg, ...)
{
  va_list args;
  va_start(args, msg);
  Log("WARNING", tag, msg, args);
  va_end(args);
}

void LogTagError(const char *tag, const char *msg, ...)
{
  va_list args;
  va_start(args, msg);
  Log("ERROR", tag, msg, args);
  va_end(args);
}

void LogTagFatal(const char *tag, const char *msg, ...)
{
  va_list args;
  va_start(args, msg);
  Log("FATAL", tag, msg, args);
  va_end(args);
}

void DisposeLogger()
{
  CloseHandle(hLogFile);
}

