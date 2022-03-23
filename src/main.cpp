#include "analyser.hpp"
#include "gui.hpp"
#include "loader.hpp"
#include "renderer.hpp"
#include "simulator.hpp"
#include "timer.hpp"
#include "window.hpp"

#include <iostream>

int main(void)
{
    Window window({ "Crisp Solutions - Simulator", 1280, 720 });
    window.Init(true);
    Simulator::Properties simulatorProps;
    simulatorProps.MaxParticles  = 1500;
    simulatorProps.ParticleCount = 500;
    simulatorProps.ParticleSize  = 0.025f;
    Simulator::Init(simulatorProps, "res/particle.shader");

    Analyser::Properties analyserProps;
    analyserProps.ShowBoundingBoxes = true;
    analyserProps.BoundingBoxColor  = ImColor(1.0f, 1.0f, 1.0f);
    Analyser::Init(&Simulator::GetFramebuffer(), analyserProps);

    Gui::Init(&window, simulatorProps.MaxParticles);

    Timer timer;
    timer.Start();

    while (!window.ShouldClose())
    {
        timer.Stop();
        double dt = timer.Milliseconds();
        timer.Start();
        Renderer::NewFrame();
        Simulator::Update(dt, Simulator::GetProperties()->ParticleSize);
        Analyser::Update();
        Gui::Update(&Simulator::GetFramebuffer(), Analyser::GetTexture(),
                    Simulator::GetProperties(), Analyser::GetProperties());
        window.Update();
    }

    Simulator::Terminate();
    Analyser::Terminate();
    Loader::CleanUp();
    Gui::Terminate();
    window.Terminate();

    return 0;
}