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

    Simulator::Init(100, "res/particle.shader");

    Gui::Init(&window);

    while (!window.ShouldClose())
    {
        Renderer::NewFrame();
        Simulator::Update();
        Gui::Update(&Simulator::GetFramebuffer(), &Simulator::GetFramebuffer());
        window.Update();
    }

    Simulator::Terminate();
    Loader::CleanUp();
    Gui::Terminate();
    window.Terminate();

    return 0;
}