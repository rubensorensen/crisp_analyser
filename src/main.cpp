#include "loader.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "window.hpp"

#include <iostream>

int main(void)
{
    Window window({ "Crisp Solutions - Simulator", 1280, 720 });
    window.Init(true);

    float vertices[]   = { -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f };
    uint32_t indices[] = { 0, 1, 3, 3, 1, 2 };

    RawModel model = Loader::LoadToVAO(vertices, sizeof(vertices), indices, sizeof(indices));
    Shader shader("res/basic.shader");

    while (!window.ShouldClose())
    {
        Renderer::NewFrame();
        shader.Bind();
        Renderer::RenderModel(model);
        shader.Unbind();
        window.Update();
    }

    Loader::CleanUp();
    window.Terminate();

    return 0;
}