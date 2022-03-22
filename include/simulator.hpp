#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "frame_buffer.hpp"
#include "particle.hpp"
#include "shader.hpp"

#include <string>
#include <vector>

class Simulator
{
  public:

    struct Properties
    {
        uint32_t MaxParticles;
        uint32_t ParticleCount;
    };

    static void Init(Properties, std::string);
    static void Update();
    static void Terminate();

    inline static Framebuffer& GetFramebuffer() { return *(Get().m_Framebuffer); }
    inline static Properties* GetProperties() { return &Get().m_Properties; }

  private:

    Simulator() {}
    ~Simulator()                = default;
    Simulator(const Simulator&) = delete;
    static Simulator& Get();

  private:

    std::vector<Particle*> m_Particles;
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<Framebuffer> m_Framebuffer;
    Properties m_Properties;
};

#endif  // SIMULATOR_HPP