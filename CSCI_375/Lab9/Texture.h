#pragma once

#include <string>
#include <GL/glew.h>
#include <FreeImagePlus.h>
#include "ShaderProgram.h"

class Texture
{
public:

	Texture(const std::string& filename);

	// Disable default copy ctor and copy assignment
  	Texture (const Texture&) = delete;
  	Texture& operator= (const Texture&) = delete;

	~Texture();

	void
	setSWrapMode (GLint sWrapMode);

	void
	setTWrapMode (GLint tWrapMode);

	void
	setMinFilter (GLint minFilter);

	void
	setMagFilter (GLint magFilter);

	void
	setTextureData(const std::string& fileNameString);

	void
	prepare();

	void
	unload();

	void
	bind(int index = 0);

	void
	bind(ShaderProgram* shaderProgram, int index = 0);

	void
	unbind();

	GLuint
	getId() const;

private:

	GLuint m_textureId;
	GLubyte* m_textureData;
	GLuint m_imageWidth;
	GLuint m_imageHeight;

	FIBITMAP* m_bitmap;
	FIBITMAP* m_bitmap32;

	int m_bitsPerPixel;
};