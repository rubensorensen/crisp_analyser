#include "renderer.hpp"

#include "GL/glew.h"
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "math.hpp"
#include "shader.hpp"

#include <iostream>

void Renderer::NewFrame()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::RenderModel(const RawModel& model)
{
    glBindVertexArray(model.GetVertexArrayObject());
    glEnableVertexAttribArray(0);
    glDrawElements(GL_TRIANGLES, model.GetVertexCount(), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Renderer::RenderParticle(const Particle& particle, Shader* shader)
{
    const RawModel& model = particle.GetModel();
    glBindVertexArray(model.GetVertexArrayObject());
    glEnableVertexAttribArray(0);

    glm::mat4x4 transform = Math::CreateTransformationMatrix(
        particle.GetPosition(), particle.GetRotation().x, particle.GetRotation().y,
        particle.GetRotation().z, particle.GetScale());
    shader->SetUniformMatrix4x4("transformationMatrix", transform);

    glDrawElements(GL_TRIANGLES, model.GetVertexCount(), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}