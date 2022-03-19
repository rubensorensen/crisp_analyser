#include "renderer.hpp"

#include "GL/glew.h"

#include <iostream>

void Renderer::NewFrame()
{
    glClearColor(0.5f, 1.0f, 1.0f, 1.0f);
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