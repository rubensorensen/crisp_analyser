#include "simulator.hpp"

#include "renderer.hpp"

#include <iostream>

Simulator& Simulator::Get()
{
    static Simulator instance;
    return instance;
}

void Simulator::Init(Simulator::Properties props, std::string shaderPath)
{
    Get().m_Properties = props;
    Get().m_Shader     = std::make_unique<Shader>(shaderPath);
    for (int i = 0; i < Get().m_Properties.MaxParticles; ++i)
        Get().m_Particles.push_back(
            new Particle({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.025f));

    Framebuffer::Properties fbProps;
    fbProps.Width       = 1280;
    fbProps.Height      = 720;
    Get().m_Framebuffer = std::make_unique<Framebuffer>(fbProps);
}

void Simulator::Update(double dt)
{
    Get().m_Framebuffer->Bind();
    Renderer::NewFrame();
    Get().m_Shader->Bind();
    Get().m_Shader->SetUniform3f("u_Color", 0.96f, 0.13f, 0.15f);

    std::vector<Particle*>& particles = Get().m_Particles;
    for (int i = 0; i < Get().m_Properties.ParticleCount; ++i)
    {
        particles[i]->Update(dt);
        Renderer::RenderParticle(*(particles[i]), &(*Get().m_Shader));
    }
    Get().m_Shader->Unbind();
    Get().m_Framebuffer->Unbind();
}

void Simulator::Terminate()
{
    for (Particle* particle : Get().m_Particles)
        delete particle;
}