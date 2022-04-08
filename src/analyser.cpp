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

void Analyser::StepOne(cv::Mat& imgIn, cv::Mat& imgOut)
{
    cv::inRange(imgIn, cv::Scalar(0, 100, 100), cv::Scalar(179, 255, 255), imgOut);
}

void Analyser::StepTwo(cv::Mat& imgIn, cv::Mat& imgOut)
{
    cv::GaussianBlur(imgIn, imgOut, cv::Size(31, 31), 6, 6);
}

void Analyser::StepThree(cv::Mat& imgIn, cv::Mat& imgOut)
{
    int t = Get().m_Properties.ContourTightness * 99.0f + 1.0f;
    cv::inRange(imgIn, cv::Scalar(t, t, t), cv::Scalar(255, 255, 255), imgOut);
}

void Analyser::StepFour(std::vector<std::vector<cv::Point>>& contours, cv::Mat& imgOut)
{
    int r = static_cast<int>(Get().m_Properties.LineColor[0] * 255);
    int g = static_cast<int>(Get().m_Properties.LineColor[1] * 255);
    int b = static_cast<int>(Get().m_Properties.LineColor[2] * 255);
    cv::drawContours(imgOut, contours, -1, cv::Scalar(b, g, r), Get().m_Properties.LineThickness);
}

void Analyser::StepFive(std::vector<cv::Rect>& boundRect, cv::Mat& imgOut)
{
    int r                          = static_cast<int>(Get().m_Properties.LineColor[0] * 255);
    int g                          = static_cast<int>(Get().m_Properties.LineColor[1] * 255);
    int b                          = static_cast<int>(Get().m_Properties.LineColor[2] * 255);
    Get().m_Properties.AreaOfBoxes = 0.0f;
    for (size_t i = 0; i < boundRect.size(); ++i)
    {
        cv::rectangle(imgOut, boundRect[i], cv::Scalar(b, g, r), Get().m_Properties.LineThickness);
        Get().m_Properties.AreaOfBoxes += boundRect[i].area();
    }

    Get().m_Properties.AreaOfAnalysisWindow = imgOut.size().area();
}

void Analyser::Update()
{
    cv::Mat origImg = GetCVMatFromGLTex();
    cv::Mat images[7];
    images[0] = origImg;

    cv::cvtColor(images[0], images[1], cv::COLOR_BGR2HSV);

    Get().StepOne(images[1], images[1]);
    Get().StepTwo(images[1], images[2]);
    Get().StepThree(images[2], images[3]);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(images[3], contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    std::vector<std::vector<cv::Point>> contoursPoly(contours.size());
    std::vector<cv::Rect> boundRect(contours.size());

    for (size_t i = 0; i < contours.size(); i++)
    {
        cv::approxPolyDP(contours[i], contoursPoly[i], 3, true);
        boundRect[i] = cv::boundingRect(contoursPoly[i]);
    }

    images[4] = cv::Mat::zeros(origImg.size(), CV_8UC3);
    images[5] = cv::Mat::zeros(origImg.size(), CV_8UC3);
    images[6] = origImg.clone();
    Get().StepFour(contours, images[4]);
    Get().StepFive(boundRect, images[5]);
    Get().StepFive(boundRect, images[6]);

    GetGLTexFromCVMat(images[Get().m_Properties.Process]);
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

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.cols, img.rows, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 img.ptr());
}