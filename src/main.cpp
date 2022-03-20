#include "loader.hpp"
#include "renderer.hpp"
#include "simulator.hpp"
#include "window.hpp"

#include <iostream>

int main(void)
{
    Window window({ "Crisp Solutions - Simulator", 1280, 720 });
    window.Init(true);

    Simulator::Init(1, "res/basic.shader");

    while (!window.ShouldClose())
    {
        Renderer::NewFrame();
        Simulator::Update();
        window.Update();
    }

    Simulator::Terminate();
    Loader::CleanUp();
    window.Terminate();

    return 0;
}