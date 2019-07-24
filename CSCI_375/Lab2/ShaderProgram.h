// ShaderProgram class to simplify shader-based programming in OpenGL
// Author: Gary M. Zoppetti, Ph.D.

#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <string>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>

class ShaderProgram
{
public:
  ShaderProgram ();

  ~ShaderProgram ();

  GLint
  getAttributeLocation (const std::string& attributeName) const;

  GLint
  getUniformLocation (const std::string& uniformName) const;

  void
  setUniformMatrix (const std::string& uniform, const glm::mat4x4& value);

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
