#ifndef ANALYSER_HPP
#define ANALYSER_HPP

#include "frame_buffer.hpp"
#include "imgui.h"
#include <opencv2/core.hpp>

class Analyser
{
  public:

    struct Properties
    {
        int Process        = 0;
        float LineColor[3] = { 1.0f, 1.0f, 0.0f };
        int LineThickness  = 2;
        int AreaOfBoxes;
        int AreaOfAnalysisWindow;
    };

    static void Init(Framebuffer*, Properties);
    static void Update();
    static void Terminate();

    inline static uint32_t GetTexture() { return Get().m_TextureID; }
    inline static Properties* GetProperties() { return &Get().m_Properties; }

  private:

    Analyser() {}
    ~Analyser()               = default;
    Analyser(const Analyser&) = delete;
    static Analyser& Get();

    static cv::Mat GetCVMatFromGLTex();
    static void GetGLTexFromCVMat(cv::Mat&);

    void StepOne(cv::Mat&, cv::Mat&);
    void StepTwo(cv::Mat&, cv::Mat&);
    void StepThree(cv::Mat&, cv::Mat&);
    void StepFour(std::vector<std::vector<cv::Point>>&, cv::Mat&);
    void StepFive(std::vector<cv::Rect>&, cv::Mat&);

  private:

    Properties m_Properties;
    Framebuffer* m_SimBuffer;
    uint32_t m_TextureID;
};

#endif  // ANALYSER_HPP