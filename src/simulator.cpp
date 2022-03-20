#include "simulator.hpp"

#include "renderer.hpp"

#include <iostream>

Simulator& Simulator::Get()
{
    static Simulator instance;
    return instance;
}

void Simulator::Init(uint32_t maxParticles, std::string shaderPath)
{
    Get().m_Shader = std::make_unique<Shader>(shaderPath);
    for (int i = 0; i < maxParticles; ++i)
        Get().m_Particles.push_back(new Particle({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.1f));

    Framebuffer::Properties fbProps;
    fbProps.Width       = 1280;
    fbProps.Height      = 720;
    Get().m_Framebuffer = std::make_unique<Framebuffer>(fbProps);
}

void Simulator::Update()
{
    Get().m_Framebuffer->Bind();
    Get().m_Shader->Bind();
    Get().m_Shader->SetUniform3f("u_Color", 1.0f, 0.0f, 0.0f);

    for (Particle* particle : Get().m_Particles)
    {
        particle->Update();
        Renderer::RenderParticle(*particle, &(*Get().m_Shader));
    }
    Get().m_Shader->Unbind();
    Get().m_Framebuffer->Unbind();
}

void Simulator::Terminate()
{
    for (Particle* particle : Get().m_Particles)
        delete particle;
}