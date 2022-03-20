#ifndef FRAME_BUFFER_HPP
#define FRAME_BUFFER_HPP

#include <stdint.h>

class Framebuffer
{
  public:

    struct Properties
    {
        uint32_t Width, Height;
    };

    Framebuffer(const Properties& properties);
    ~Framebuffer();

    inline const Properties& GetProperties() const { return m_Properties; }
    inline uint32_t GetColorAttachment() const { return m_ColorAttachmentID; }

    void Resize();
    void Bind();
    void Unbind();

  private:

    Properties m_Properties;
    uint32_t m_RendererID;
    uint32_t m_ColorAttachmentID;
};

#endif  // FRAME_BUFFER_HPP