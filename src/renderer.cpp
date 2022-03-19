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
    glDrawArrays(GL_TRIANGLES, 0, model.GetVertexCount());
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}