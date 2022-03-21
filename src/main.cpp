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
    const int32_t maxParticles = 1000;
    int32_t particleCount      = 500;

    Simulator::Init(maxParticles, "res/particle.shader");

    Gui::Init(&window);

    while (!window.ShouldClose())
    {
        Renderer::NewFrame();
        Simulator::Update(&particleCount);
        Gui::Update(&Simulator::GetFramebuffer(), &Simulator::GetFramebuffer(), &particleCount);
        window.Update();
    }

    Simulator::Terminate();
    Loader::CleanUp();
    Gui::Terminate();
    window.Terminate();

    return 0;
}