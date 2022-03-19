#include "loader.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "window.hpp"

#include <iostream>

int main(void)
{
    Window window({ "Crisp Solutions - Simulator", 1280, 720 });
    window.Init(true);

    Renderer renderer;

    float vertices[] = { // Left bottom triangle
                         -0.5f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f,
                         // Right bottom triangle
                         0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, -0.5f, 0.5f, 0.0f
    };

    RawModel model = Loader::LoadToVAO(vertices, sizeof(vertices));
    Shader shader("res/basic.shader");

    while (!window.ShouldClose())
    {
        renderer.Prepare();
        shader.Bind();
        renderer.RenderModel(model);
        shader.Unbind();
        window.Update();
    }

    Loader::CleanUp();
    window.Terminate();

    return 0;
}