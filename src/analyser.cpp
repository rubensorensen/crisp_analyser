#include "analyser.hpp"

#include "GL/glew.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

Analyser& Analyser::Get()
{
    static Analyser instance;
    return instance;
}

void Analyser::Init(Framebuffer* simBuffer)
{
    Get().m_SimBuffer = simBuffer;
}

void Analyser::Update()
{
    GetCVMatFromGLTex();

    GetGLTexFromCVMat();
}

void Analyser::Terminate()
{
    glDeleteTextures(1, &Get().m_TextureID);
}

void Analyser::GetCVMatFromGLTex()
{
    glBindTexture(GL_TEXTURE_2D, Get().m_SimBuffer->GetColorAttachment());
    GLenum gl_texture_width, gl_texture_height;

    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, (GLint*)&gl_texture_width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, (GLint*)&gl_texture_height);

    static unsigned char* gl_texture_bytes =
        (unsigned char*)malloc(sizeof(unsigned char) * gl_texture_width * gl_texture_height * 3);
    glGetTexImage(GL_TEXTURE_2D, 0 /* mipmap level */, GL_BGR, GL_UNSIGNED_BYTE, gl_texture_bytes);

    Get().m_Mat = cv::Mat(gl_texture_height, gl_texture_width, CV_8UC3, gl_texture_bytes);
}

void Analyser::GetGLTexFromCVMat()
{
    glBindTexture(GL_TEXTURE_2D, Get().m_TextureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    cv::cvtColor(Get().m_Mat, Get().m_Mat, cv::COLOR_RGB2BGR);

    glTexImage2D(GL_TEXTURE_2D,       // Type of texture
                 0,                   // Pyramid level (for mip-mapping) - 0 is the top level
                 GL_RGB,              // Internal colour format to convert to
                 Get().m_Mat.cols,    // Image width  i.e. 640 for Kinect in standard mode
                 Get().m_Mat.rows,    // Image height i.e. 480 for Kinect in standard mode
                 0,                   // Border width in pixels (can either be 1 or 0)
                 GL_RGB,              // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
                 GL_UNSIGNED_BYTE,    // Image data type
                 Get().m_Mat.ptr());  // The actual image data itself
}