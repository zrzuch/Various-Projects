// ShaderProgram class to simplify shader-based programming in OpenGL
// Author: Gary M. Zoppetti, Ph.D.

#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <iostream>
#include <string>

#include <GL/glew.h>

class ShaderProgram
{
public:
  ShaderProgram ();

  ~ShaderProgram ();

  GLint
  getAttributeLocation (const std::string& attributeName) const;

  void
  createVertexShader (const std::string& vertexShaderFilename);

  void
  createFragmentShader (const std::string& fragmentShaderFilename);

  void
  link () const;

  void
  enable ();

  void
  disable ();

private:
  void
  compileShader (const std::string& shaderFilename, GLuint shaderId);

  std::string
  readShaderSource (const std::string& filename) const;

  void
  writeInfoLog (GLuint shaderId, bool isShader,
		const std::string& logFilename) const;

private:
  GLuint m_programId;
  GLuint m_vertexShaderId;
  GLuint m_fragmentShaderId;
};

#endif
