#include "application.hpp"

#include "analyser.hpp"
#include "gui.hpp"
#include "loader.hpp"
#include "renderer.hpp"
#include "simulator.hpp"
#include "timer.hpp"

Application::Application(const char* name, uint32_t width, uint32_t height)
{
    Window::Properties windowProps;
    windowProps.Title  = name;
    windowProps.Width  = width;
    windowProps.Height = height;
    m_Window           = std::make_unique<Window>(windowProps);

    m_Window->Init(true);
    Simulator::Properties simulatorProps;
    simulatorProps.MaxParticles  = 1500;
    simulatorProps.ParticleCount = 500;
    simulatorProps.ParticleSize  = 0.025f;
    simulatorProps.ParticleSpeed = 1.0f;
    Simulator::Init(simulatorProps, "res/particle.shader");

    Analyser::Properties analyserProps;
    analyserProps.Process          = 0;
    analyserProps.LineColor[0]     = 1.0f;
    analyserProps.LineColor[1]     = 1.0f;
    analyserProps.LineColor[2]     = 0.0f;
    analyserProps.LineThickness    = 2;
    analyserProps.ContourTightness = 0.5f;
    Analyser::Init(&Simulator::GetFramebuffer(), analyserProps);

    Gui::Init(m_Window.get(), simulatorProps.MaxParticles);
}

Application::~Application()
{
    Simulator::Terminate();
    Analyser::Terminate();
    Loader::CleanUp();
    Gui::Terminate();
    m_Window->Terminate();
}

void Application::Run()
{
    Timer::Init();
    while (!m_Window->ShouldClose())
    {
        Renderer::NewFrame();
        Simulator::Update(Timer::DeltaTime(), Simulator::GetProperties()->ParticleSize);
        Analyser::Update();
        Gui::Update(&Simulator::GetFramebuffer(), Analyser::GetTexture(),
                    Simulator::GetProperties(), Analyser::GetProperties());
        m_Window->Update();
    }
}