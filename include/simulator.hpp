#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "particle.hpp"
#include "shader.hpp"
#include "vector"

#include <string>

class Simulator
{
  public:

    static void Init(uint32_t, std::string);
    static void Update();
    static void Terminate();

  private:

    Simulator() {}
    ~Simulator()                = default;
    Simulator(const Simulator&) = delete;
    static Simulator& Get();

  private:

    std::vector<Particle*> m_Particles;
    std::unique_ptr<Shader> m_Shader;
};

#endif  // SIMULATOR_HPP