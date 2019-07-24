#include "Texture.h"
#include <iostream>

Texture::Texture(const std::string& filename)
    : m_textureId()
    , m_textureData()
    , m_imageWidth()
    , m_imageHeight()
{
    // Generate a texture ID and bind to it
    glGenTextures(1, &m_textureId);
    setTextureData(filename);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_textureId);
    unload();
}

// Set the S wrapping mode. 
//   Options are GL_REPEAT (default), GL_MIRRORED_REPEAT,
//     GL_CLAMP_TO_EDGE, and GL_CLAMP_TO_BORDER.
// Precondition: This texture MUST be bound!
void
Texture::setSWrapMode (GLint sWrapMode)
{
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrapMode);
}

// Set the T wrapping mode. 
//   Options are GL_REPEAT (default), GL_MIRRORED_REPEAT,
//     GL_CLAMP_TO_EDGE, and GL_CLAMP_TO_BORDER.
// Precondition: This texture MUST be bound!
void
Texture::setTWrapMode (GLint tWrapMode)
{
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrapMode);
}

// Set the minification filter. 
//   Options are GL_NEAREST, GL_LINEAR,
//     GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR,
//     GL_LINEAR_MIPMAP_NEAREST, and GL_LINEAR_MIPMAP_LINEAR. 
// NOTE: This texture MUST be bound!
void
Texture::setMinFilter (GLint minFilter)
{
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
}

// Set the magnification filter. 
//   Options are GL_NEAREST and GL_LINEAR.
// NOTE: This texture MUST be bound!
void
Texture::setMagFilter (GLint magFilter)
{
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

// Need to unload previously buffered data
// Source: https://r3dux.org/2014/10/how-to-load-an-opengl-texture-using-the-freeimage-library-or-freeimageplus-technically/
void
Texture::setTextureData(const std::string& fileNameString)
{
    const char* fileName = fileNameString.c_str();
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(fileName , 0);
	if (format == -1)
    {
        std::cout << "Could not find image: " << fileNameString << " - Aborting." << std::endl;
        exit(-1);
    }
    // Found image, but couldn't determine the file format? Try again...
    if (format == FIF_UNKNOWN)
    {
        std::cout << "Couldn't determine file format - attempting to get from file extension..." << std::endl;
        // ...by getting the filetype from the filename extension (i.e. .PNG, .GIF etc.)
        // Note: This is slower and more error-prone that getting it from the file itself,
        // also, we can't use the 'U' (unicode) variant of this method as that's Windows only.
        format = FreeImage_GetFIFFromFilename(fileName);
        // Check that the plugin has reading capabilities for this format (if it's FIF_UNKNOWN,
        // for example, then it won't have) - if we can't read the file, then we bail out =(
        if ( !FreeImage_FIFSupportsReading(format) )
        {
            std::cout << "Detected image format cannot be read!" << std::endl;
            exit(-1);
        }
    }
    // If we're here we have a known image format, so load the image into a bitap
    m_bitmap = FreeImage_Load(format, fileName);
    // How many bits-per-pixel is the source image?
    m_bitsPerPixel =  FreeImage_GetBPP(m_bitmap);
    // Convert our image up to 32 bits (8 bits per channel, Red/Green/Blue/Alpha) -
    // but only if the image is not already 32 bits (i.e. 8 bits per channel).
    // Note: ConvertTo32Bits returns a CLONE of the image data - so if we
    // allocate this back to itself without using our bitmap32 intermediate
    // we will LEAK the original bitmap data, and valgrind will show things like this:
    //
    // LEAK SUMMARY:
    //  definitely lost: 24 bytes in 2 blocks
    //  indirectly lost: 1,024,874 bytes in 14 blocks    <--- Ouch.
    //
    // Using our intermediate and cleaning up the initial bitmap data we get:
    //
    // LEAK SUMMARY:
    //  definitely lost: 16 bytes in 1 blocks
    //  indirectly lost: 176 bytes in 4 blocks
    //
    // All above leaks (192 bytes) are caused by XGetDefault (in /usr/lib/libX11.so.6.3.0) - we have 
    // no control over this.
    if (m_bitsPerPixel == 32)
    {
        std::cout << "Source image has " << m_bitsPerPixel << " bits per pixel. Skipping conversion." << std::endl;
        m_bitmap32 = m_bitmap;
    }
    else
    {
        std::cout << "Source image has " << m_bitsPerPixel << " bits per pixel. Converting to 32-bit colour." 
            << std::endl;
        m_bitmap32 = FreeImage_ConvertTo32Bits(m_bitmap);
    }
    // Some basic image info - strip it out if you don't care
    m_imageWidth  = static_cast<GLuint>(FreeImage_GetWidth(m_bitmap32));
    m_imageHeight = static_cast<GLuint>(FreeImage_GetHeight(m_bitmap32));
    std::cout << "Image: " << fileNameString << " is size: " << m_imageWidth << "x" << m_imageHeight 
        << "." << std::endl;
    // Get a pointer to the texture data as an array of unsigned bytes.
    // Note: At this point bitmap32 ALWAYS holds a 32-bit colour version of our image - so we get our data 
    // from that. Also, we don't need to delete or delete[] this textureData because it's not on the heap 
    // (so attempting to do so will cause a crash) - just let it go out of scope and the memory will be 
    // returned to the stack.
    m_textureData = static_cast<GLubyte*>(FreeImage_GetBits(m_bitmap32));
}

void
Texture::prepare()
{
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    // Upload texture data to OpenGL.
    // Construct the texture.
    // Note: The 'Data format' is the format of the image data as provided by the image library. 
    //      FreeImage decodes images into BGR/BGRA format, but we want to work with it in the more 
    //      common RGBA format, so we specify the 'Internal format' as such.
    glTexImage2D(GL_TEXTURE_2D,    // Type of texture
                 0,                // Mipmap level (0 being the top level i.e. full size) | Level should be 0, unless manually specifying mipmaps
                 GL_RGBA,          // Internal format
                 m_imageWidth,     // Width of the texture
                 m_imageHeight,    // Height of the texture,
                 0,                // Border in pixels | Border is a legacy parameter and should be set to 0
                 GL_BGRA,          // Data format
                 GL_UNSIGNED_BYTE, // Type of texture data
                 m_textureData);   // The image data to use for this texture
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void
Texture::unload()
{
    // Unload the 32-bit colour bitmap
    FreeImage_Unload(m_bitmap32);
    // If we had to do a conversion to 32-bit colour, then unload the original
    // non-32-bit-colour version of the image data too. Otherwise, bitmap32 and
    // bitmap point at the same data, and that data's already been free'd, so
    // don't attempt to free it again! (or we'll crash).
    // Has to be saved and deleted here or it will crash
    if (m_bitsPerPixel != 32)
    {
        FreeImage_Unload(m_bitmap);
    }
}

void
Texture::bind(int index)
{
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
}

void
Texture::bind(ShaderProgram* shaderProgram, int index)
{
    bind(index);
    shaderProgram->setUniform("uSamplerIndex", index);
}

void
Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint
Texture::getId() const
{
	return m_textureId;
}