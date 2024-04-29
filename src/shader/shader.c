#include "shader.h"
#include "glad/glad.h"
#include <string.h>
#include "../utility/error.h"
#include "pico_headers/pico_log.h"

static long lLastUsedShader = -1;
void UseShader(Shader shader)
{
  glUseProgram(shader);
  lLastUsedShader = shader;
}


void CheckCompileError(unsigned int object, char *type)
{
  int success;
  char infoLog[1024];

  if(strcmp(type, "PROGRAM") == 0)
  {
    glGetProgramiv(object, GL_LINK_STATUS, &success);
    
    if(!success)
    {
      glGetProgramInfoLog(object, 1024, NULL, infoLog);
      log_fatal("Error while linking program: %s\nmessage: %s.", type, infoLog);
      FATAL_ERROR();
    }
  }
  else
  {
    glGetShaderiv(object, GL_COMPILE_STATUS, &success);
    
    if(!success)
    {
      glGetShaderInfoLog(object, 1024, NULL, infoLog);
      log_fatal("Error while compiling shader: %s\nmessage: %s.",type, infoLog);
      FATAL_ERROR();
    }
  }
}

Shader CompileShader(const char *vertexSource, const char *fragmentSource, const char *geometrySource)
{
  log_trace("Compiling and linking shaders.");
  unsigned int sVertex, sFragment, sGeometry;

  //Vertex shader
  log_trace("Compiling vertex shader.");
  sVertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(sVertex, 1, &vertexSource, NULL);
  glCompileShader(sVertex);
  CheckCompileError(sVertex, "VERTEX");
  log_trace("Vertex shader compiled.");

  //Fragment shader
  log_trace("Compiling fragment shader.");
  sFragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(sFragment, 1, &fragmentSource, NULL);
  glCompileShader(sFragment);
  CheckCompileError(sFragment, "FRAGMENT");
  log_trace("Fragment shader compiled.");

  //Geometry shader
  if(geometrySource != NULL)
  {
    log_trace("Compiling geometry shader.");
    sGeometry = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(sGeometry, 1, &geometrySource, NULL);
    glCompileShader(sGeometry);
    CheckCompileError(sGeometry, "GEOMETRY");
    log_trace("Geometry shader compiled.");
  }

  //Shader program
  Shader shader = glCreateProgram();
  glAttachShader(shader, sVertex);
  glAttachShader(shader, sFragment);
  if(geometrySource != NULL)
    glAttachShader(shader, sGeometry);

  log_trace("Linking shader program.");
  glLinkProgram(shader);
  CheckCompileError(shader, "PROGRAM");
  log_trace("Shader program linked.");

  glDeleteShader(sVertex);
  glDeleteShader(sFragment);
  if(geometrySource != NULL)
    glDeleteShader(sGeometry);

  log_trace("Shaders compiled and linked.");
  return shader;
}

void _UseShaderIfNeeded(Shader shader)
{
  if(lLastUsedShader != shader)
  {
    UseShader(shader);
  }
}

void ShaderSetFloat(Shader shader, const char *name, float value)
{
  _UseShaderIfNeeded(shader);
  glUniform1f(glGetUniformLocation(shader, name), value);
}

void ShaderSetInteger(Shader shader, const char *name, int value)
{
  _UseShaderIfNeeded(shader);
  glUniform1i(glGetUniformLocation(shader, name), value);
}

void ShaderSetVector2f(Shader shader, const char *name, float x, float y)
{
  _UseShaderIfNeeded(shader);
  glUniform2f(glGetUniformLocation(shader, name), x, y);
}

void ShaderSetVector3f(Shader shader, const char *name, float x, float y, float z)
{
  _UseShaderIfNeeded(shader);
  glUniform3f(glGetUniformLocation(shader, name), x, y, z);
}

void ShaderSetVector4f(Shader shader, const char *name, float x, float y, float z, float w)
{
  _UseShaderIfNeeded(shader);
  glUniform4f(glGetUniformLocation(shader, name), x, y, z, w);
}

void ShaderSetVector2(Shader shader, const char *name, vec2 value)
{
  _UseShaderIfNeeded(shader);
  glUniform2fv(glGetUniformLocation(shader, name), 1, value);
}

void ShaderSetVector3(Shader shader, const char *name, vec3 value)
{
  _UseShaderIfNeeded(shader);
  glUniform3fv(glGetUniformLocation(shader, name), 1, value);
}

void ShaderSetVector4(Shader shader, const char *name, float *value)
{
  _UseShaderIfNeeded(shader);
  glUniform4fv(glGetUniformLocation(shader, name), 1, value);
}

void ShaderSetMat4(Shader shader, const char *name, mat4 value)
{
  _UseShaderIfNeeded(shader);
  glUniformMatrix4fv(glGetUniformLocation(shader, name), 1, GL_FALSE, value[0]);
}
