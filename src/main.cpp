#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "loader.hpp"
#include "math.hpp"
#include "particle.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "window.hpp"

#include <iostream>
#include <random>
#include <vector>

int main(void)
{
    Window window({ "Crisp Solutions - Simulator", 1280, 720 });
    window.Init(true);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-1, 1);

    std::vector<Particle*> particles;

    for (int i = 0; i < 100; ++i)
        particles.push_back(new Particle({ (float)dist(gen), (float)dist(gen), (float)dist(gen) },
                                         { 0.0f, 0.0f, 0.0f }, ((float)dist(gen) + 1.0) / 10.0f));

    Shader shader("res/basic.shader");

    while (!window.ShouldClose())
    {
        Renderer::NewFrame();
        shader.Bind();

        for (Particle* p : particles)
        {
            Renderer::RenderParticle(*p, &shader);
        }
        shader.Unbind();
        window.Update();
    }

    for (Particle* p : particles)
        delete p;

    Loader::CleanUp();
    window.Terminate();

    return 0;
}