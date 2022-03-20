#include "simulator.hpp"

#include "renderer.hpp"

Simulator& Simulator::Get()
{
    static Simulator instance;
    return instance;
}

void Simulator::Init(uint32_t maxParticles, std::string shaderPath)
{
    Get().m_Shader = std::make_unique<Shader>(shaderPath);
    for (int i = 0; i < maxParticles; ++i)
        Get().m_Particles.push_back(new Particle({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 1.0f));
}

void Simulator::Update()
{
    Get().m_Shader->Bind();

    for (Particle* particle : Get().m_Particles)
        Renderer::RenderParticle(*particle, &(*Get().m_Shader));
    Get().m_Shader->Unbind();
}

void Simulator::Terminate()
{
    for (Particle* particle : Get().m_Particles)
        delete particle;
}