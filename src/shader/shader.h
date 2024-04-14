/// @file
#ifndef SHADER_H
#define SHADER_H

#include "cglm/types.h"

/// typedef for shader handle.
typedef unsigned int Shader;

/// @brief Sets specified shader as currently used by OpenGL
///
/// @param[in] shader Shader to be used.
void UseShader(Shader shader);
/// @brief Compiles and links specified shader sources into a shader program.
///
/// @param[in] vertexSource Source of vertex shader.
/// @param[in] fragmentSource Source of fragment shader.
/// @param[in] geometrySource _optional_ Source of geometry shader. Use NULL if not required.
/// @returns Handle to compiled shader program.
Shader CompileShader(const char *vertexSource, const char *fragmentSource, const char *geometrySource);

/// @brief Sets float uniform in shader
///
/// @param[in] shader Shader for which uniform will be set.
/// @param[in] name Name of the uniform.
/// @param[in] value Value to set.
void ShaderSetFloat(Shader shader, const char *name, float value);
/// @brief Sets integer uniform in shader
///
/// @param[in] shader Shader for which uniform will be set.
/// @param[in] name Name of the uniform.
void ShaderSetInteger(Shader shader, const char *name, int value);
/// @brief Sets vec2 uniform in shader
///
/// @param[in] shader Shader for which uniform will be set.
/// @param[in] name Name of the uniform.
void ShaderSetVector2f(Shader shader, const char *name, float x, float y);
/// @brief Sets vec3 uniform in shader
///
/// @param[in] shader Shader for which uniform will be set.
/// @param[in] name Name of the uniform.
void ShaderSetVector3f(Shader shader, const char *name, float x, float y, float z);
/// @brief Sets vec4 uniform in shader
///
/// @param[in] shader Shader for which uniform will be set.
/// @param[in] name Name of the uniform.
void ShaderSetVector4f(Shader shader, const char *name, float x, float y, float z, float w);
/// @brief Sets vec2 uniform in shader
///
/// @param[in] shader Shader for which uniform will be set.
/// @param[in] name Name of the uniform.
void ShaderSetVector2(Shader shader, const char *name, vec2 value);
/// @brief Sets vec3 uniform in shader
/// 
/// @param[in] shader Shader for which uniform will be set.
/// @param[in] name Name of the uniform.
void ShaderSetVector3(Shader shader, const char *name, vec3 value);
/// @brief Sets vec4 uniform in shader
///
/// @param[in] shader Shader for which uniform will be set.
/// @param[in] name Name of the uniform.
void ShaderSetVector4(Shader shader, const char *name, vec4 value);
/// @brief Sets mat4 uniform in shader
///
/// @param[in] shader Shader for which uniform will be set.
/// @param[in] name Name of the uniform.
void ShaderSetMat4(Shader shader, const char *name, mat4 value);

#endif
