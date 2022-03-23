#include "analyser.hpp"

#include "GL/glew.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
Analyser& Analyser::Get()
{
    static Analyser instance;
    return instance;
}

void Analyser::Init(Framebuffer* simBuffer, Properties props)
{
    Get().m_SimBuffer  = simBuffer;
    Get().m_Properties = props;
}

void Analyser::Update()
{
    cv::Mat origImg = GetCVMatFromGLTex();
    if (Get().m_Properties.ShowBoundingBoxes)
    {
        cv::Mat img;

        cv::cvtColor(origImg, img, cv::COLOR_BGR2HSV);
        cv::inRange(img, cv::Scalar(0, 100, 100), cv::Scalar(179, 255, 255), img);
        cv::GaussianBlur(img, img, cv::Size(11, 11), 6, 6);

        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(img, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

        std::vector<std::vector<cv::Point>> contoursPoly(contours.size());
        std::vector<cv::Rect> boundRect(contours.size());

        for (size_t i = 0; i < contours.size(); i++)
        {
            cv::approxPolyDP(contours[i], contoursPoly[i], 3, true);
            boundRect[i] = cv::boundingRect(contoursPoly[i]);
        }

        int r = static_cast<int>(Get().m_Properties.BoundingBoxColor.Value.x * 255);
        int g = static_cast<int>(Get().m_Properties.BoundingBoxColor.Value.y * 255);
        int b = static_cast<int>(Get().m_Properties.BoundingBoxColor.Value.z * 255);
        Get().m_Properties.AreaOfBoxes = 0.0f;
        for (size_t i = 0; i < boundRect.size(); ++i)
        {
            cv::rectangle(origImg, boundRect[i], cv::Scalar(b, g, r), 2);
            Get().m_Properties.AreaOfBoxes += boundRect[i].area();
        }
    }

    Get().m_Properties.AreaOfAnalysisWindow = origImg.size().area();
    GetGLTexFromCVMat(origImg);
}

void Analyser::Terminate()
{
    glDeleteTextures(1, &Get().m_TextureID);
}

cv::Mat Analyser::GetCVMatFromGLTex()
{
    glBindTexture(GL_TEXTURE_2D, Get().m_SimBuffer->GetColorAttachment());
    GLenum gl_texture_width, gl_texture_height;

    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, (GLint*)&gl_texture_width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, (GLint*)&gl_texture_height);

    static unsigned char* gl_texture_bytes =
        (unsigned char*)malloc(sizeof(unsigned char) * gl_texture_width * gl_texture_height * 3);
    glGetTexImage(GL_TEXTURE_2D, 0 /* mipmap level */, GL_BGR, GL_UNSIGNED_BYTE, gl_texture_bytes);

    return cv::Mat(gl_texture_height, gl_texture_width, CV_8UC3, gl_texture_bytes);
}

void Analyser::GetGLTexFromCVMat(cv::Mat& img)
{
    glBindTexture(GL_TEXTURE_2D, Get().m_TextureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    cv::cvtColor(img, img, cv::COLOR_RGB2BGR);

    glTexImage2D(GL_TEXTURE_2D,     // Type of texture
                 0,                 // Pyramid level (for mip-mapping) - 0 is the top level
                 GL_RGB,            // Internal colour format to convert to
                 img.cols,          // Image width  i.e. 640 for Kinect in standard mode
                 img.rows,          // Image height i.e. 480 for Kinect in standard mode
                 0,                 // Border width in pixels (can either be 1 or 0)
                 GL_RGB,            // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
                 GL_UNSIGNED_BYTE,  // Image data type
                 img.ptr());        // The actual image data itself
}