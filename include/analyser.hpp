#ifndef ANALYSER_HPP
#define ANALYSER_HPP

#include "frame_buffer.hpp"
#include <opencv2/core.hpp>

class Analyser
{
  public:

    static void Init(Framebuffer*);
    static void Update();
    static void Terminate();

    inline static uint32_t GetTexture() { return Get().m_TextureID; }

  private:

    Analyser() {}
    ~Analyser()               = default;
    Analyser(const Analyser&) = delete;
    static Analyser& Get();

    static void GetCVMatFromGLTex();
    static void GetGLTexFromCVMat();

  private:

    Framebuffer* m_SimBuffer;
    cv::Mat m_Mat;
    uint32_t m_TextureID;
};

#endif  // ANALYSER_HPP