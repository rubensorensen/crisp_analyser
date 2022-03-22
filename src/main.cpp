#include "analyser.hpp"
#include "gui.hpp"
#include "loader.hpp"
#include "renderer.hpp"
#include "simulator.hpp"
#include "window.hpp"

#include <iostream>

int main(void)
{
    Window window({ "Crisp Solutions - Simulator", 1280, 720 });
    window.Init(true);
    Simulator::Properties simulatorProps;
    simulatorProps.MaxParticles  = 1500;
    simulatorProps.ParticleCount = 500;

    Simulator::Init(simulatorProps, "res/particle.shader");
    Analyser::Init(&Simulator::GetFramebuffer());

    Gui::Init(&window, simulatorProps.MaxParticles);

    while (!window.ShouldClose())
    {
        Renderer::NewFrame();
        Simulator::Update();
        Analyser::Update();
        Gui::Update(&Simulator::GetFramebuffer(), Analyser::GetTexture(),
                    &Simulator::GetProperties()->ParticleCount);
        window.Update();
    }

    Simulator::Terminate();
    Analyser::Terminate();
    Loader::CleanUp();
    Gui::Terminate();
    window.Terminate();

    return 0;
}