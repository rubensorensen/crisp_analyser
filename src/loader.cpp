#include "loader.hpp"

#include "GL/glew.h"

std::list<uint32_t> Loader::m_VertexArrayObjects;
std::list<uint32_t> Loader::m_VertexBufferObjects;

RawModel Loader::LoadToVAO(float* positions, size_t size)
{
    uint32_t vaoID = CreateVAO();
    StoreDataInAttributeLists(0, positions, size);
    UnbindVAO();
    return RawModel(vaoID, size / 3);
}

void Loader::CleanUp()
{
    for (uint32_t& vao : m_VertexArrayObjects)
        glDeleteVertexArrays(1, &vao);

    for (uint32_t& vbo : m_VertexBufferObjects)
        glDeleteBuffers(1, &vbo);
}

uint32_t Loader::CreateVAO()
{
    uint32_t vao;
    glGenVertexArrays(1, &vao);
    m_VertexArrayObjects.push_back(vao);
    glBindVertexArray(vao);
    return vao;
}

void Loader::StoreDataInAttributeLists(uint32_t attributeNumber, float* data, size_t size)
{
    uint32_t vbo;
    glGenBuffers(1, &vbo);
    m_VertexBufferObjects.push_back(vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::UnbindVAO()
{
    glBindVertexArray(0);
}