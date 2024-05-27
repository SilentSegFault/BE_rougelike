#ifndef LOGGER_H
#define LOGGER_H

#include <vadefs.h>
void InitLogger(const char *logsDirPath);

void Log(const char *logLevel, const char *tag, const char *msg, va_list args);

void LogTrace(const char *msg, ...);
void LogDebug(const char *msg, ...);
void LogInfo(const char *msg, ...);
void LogWarning(const char *msg, ...);
void LogError(const char *msg, ...);
void LogFatal(const char *msg, ...);

void LogTagTrace(const char *tag, const char *msg, ...);
void LogTagDebug(const char *tag, const char *msg, ...);
void LogTagInfo(const char *tag, const char *msg, ...);
void LogTagWarning(const char *tag, const char *msg, ...);
void LogTagError(const char *tag, const char *msg, ...);
void LogTagFatal(const char *tag, const char *msg, ...);

void DisposeLogger();

#endif
