#include "shader.h"
#include "glad/glad.h"
#include <string.h>
#include "../logger/logger.h"

void UseShader(Shader shader)
{
  glUseProgram(shader);
}


int CompileErrorOccured(unsigned int object, char *type)
{
  int success;
  char infoLog[1024];

  if(strcmp(type, "PROGRAM") == 0)
  {
    glGetProgramiv(object, GL_LINK_STATUS, &success);
    
    if(!success)
    {
      glGetProgramInfoLog(object, 1024, NULL, infoLog);
      LogError("Error while linking program: %s\nmessage: %s.", type, infoLog);
      return 1;
    }
  }
  else
  {
    glGetShaderiv(object, GL_COMPILE_STATUS, &success);
    
    if(!success)
    {
      glGetShaderInfoLog(object, 1024, NULL, infoLog);
      LogError("Error while compiling shader: %s\nmessage: %s.",type, infoLog);
      return 1;
    }
  }

  return 0;
}

int CompileShader(const char *vertexSource, const char *fragmentSource, const char *geometrySource, Shader *compiledShader)
{
  unsigned int sVertex, sFragment, sGeometry;

  //Vertex shader
  sVertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(sVertex, 1, &vertexSource, NULL);
  glCompileShader(sVertex);
  if(CompileErrorOccured(sVertex, "VERTEX"))
  {
    return 0;
  }

  //Fragment shader
  sFragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(sFragment, 1, &fragmentSource, NULL);
  glCompileShader(sFragment);
  if(CompileErrorOccured(sFragment, "FRAGMENT"))
  {
    return 0;
  }

  //Geometry shader
  if(geometrySource != NULL)
  {
    sGeometry = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(sGeometry, 1, &geometrySource, NULL);
    glCompileShader(sGeometry);
    if(CompileErrorOccured(sGeometry, "GEOMETRY"))
    {
      return 0;
    }
  }

  //Shader program
  Shader shader = glCreateProgram();
  glAttachShader(shader, sVertex);
  glAttachShader(shader, sFragment);
  if(geometrySource != NULL)
    glAttachShader(shader, sGeometry);

  glLinkProgram(shader);
  if(CompileErrorOccured(shader, "PROGRAM"))
  {
    return 0;
  }

  glDeleteShader(sVertex);
  glDeleteShader(sFragment);
  if(geometrySource != NULL)
    glDeleteShader(sGeometry);

  *compiledShader = shader;
  return 1;
}

void ShaderSetFloat(Shader shader, const char *name, float value, BOOL useShader)
{
  if(useShader)
    UseShader(shader);

  glUniform1f(glGetUniformLocation(shader, name), value);
}

void ShaderSetInteger(Shader shader, const char *name, int value, BOOL useShader)
{
  if(useShader)
    UseShader(shader);

  glUniform1i(glGetUniformLocation(shader, name), value);
}

void ShaderSetVector2f(Shader shader, const char *name, float x, float y, BOOL useShader)
{
  if(useShader)
    UseShader(shader);

  glUniform2f(glGetUniformLocation(shader, name), x, y);
}

void ShaderSetVector3f(Shader shader, const char *name, float x, float y, float z, BOOL useShader)
{
  if(useShader)
    UseShader(shader);

  glUniform3f(glGetUniformLocation(shader, name), x, y, z);
}

void ShaderSetVector4f(Shader shader, const char *name, float x, float y, float z, float w, BOOL useShader)
{
  if(useShader)
    UseShader(shader);

  glUniform4f(glGetUniformLocation(shader, name), x, y, z, w);
}

void ShaderSetVector2(Shader shader, const char *name, vec2 value, BOOL useShader)
{
  if(useShader)
    UseShader(shader);

  glUniform2fv(glGetUniformLocation(shader, name), 1, value);
}

void ShaderSetVector3(Shader shader, const char *name, vec3 value, BOOL useShader)
{
  if(useShader)
    UseShader(shader);

  glUniform3fv(glGetUniformLocation(shader, name), 1, value);
}

void ShaderSetVector4(Shader shader, const char *name, float *value, BOOL useShader)
{
  if(useShader)
    UseShader(shader);

  glUniform4fv(glGetUniformLocation(shader, name), 1, value);
}

void ShaderSetMat4(Shader shader, const char *name, mat4 value, BOOL useShader)
{
  if(useShader)
    UseShader(shader);

  glUniformMatrix4fv(glGetUniformLocation(shader, name), 1, GL_FALSE, value[0]);
}
