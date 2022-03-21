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

    static void Init(uint32_t, std::string);
    static void Update(int* particleCount);
    static void Terminate();

    inline static Framebuffer& GetFramebuffer() { return *(Get().m_Framebuffer); }

  private:

    Simulator() {}
    ~Simulator()                = default;
    Simulator(const Simulator&) = delete;
    static Simulator& Get();

  private:

    std::vector<Particle*> m_Particles;
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<Framebuffer> m_Framebuffer;
    int32_t m_MaxParticles;
};

#endif  // SIMULATOR_HPP