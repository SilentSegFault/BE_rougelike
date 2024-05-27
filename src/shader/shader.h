/// @file
#ifndef SHADER_H
#define SHADER_H

#include "cglm/types.h"
#include <windows.h>

typedef unsigned int Shader;

void UseShader(Shader shader);
int CompileShader(const char *vertexSource, const char *fragmentSource, const char *geometrySource, Shader *compiledShader);

void ShaderSetFloat(Shader shader, const char *name, float value, BOOL useShader);
void ShaderSetInteger(Shader shader, const char *name, int value, BOOL useShader );
void ShaderSetVector2f(Shader shader, const char *name, float x, float y, BOOL useShader);
void ShaderSetVector3f(Shader shader, const char *name, float x, float y, float z, BOOL useShader);
void ShaderSetVector4f(Shader shader, const char *name, float x, float y, float z, float w, BOOL useShader);
void ShaderSetVector2(Shader shader, const char *name, vec2 value, BOOL useShader);
void ShaderSetVector3(Shader shader, const char *name, vec3 value, BOOL useShader);
void ShaderSetVector4(Shader shader, const char *name, vec4 value, BOOL useShader);
void ShaderSetMat4(Shader shader, const char *name, mat4 value, BOOL useShader);

#endif
