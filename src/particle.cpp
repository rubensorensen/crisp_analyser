#include "particle.hpp"

#include "loader.hpp"

#include <stdint.h>

Particle::Particle(const glm::vec3& pos, const glm::vec3& rot, float scale)
    : m_Position(pos), m_Rotation(rot), m_Scale(scale)
{
    float vertices[] = {
        -0.5f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f
    };
    uint32_t indices[] = { 0, 1, 3, 3, 1, 2 };
    m_Model            = std::make_unique<RawModel>(
        Loader::LoadToVAO(vertices, sizeof(vertices), indices, sizeof(indices)));
}

void Particle::IncreasePosition(const glm::vec3& dPos)
{
    m_Position += dPos;
}

void Particle::IncreaseRotation(const glm::vec3& dRot)
{
    m_Rotation += dRot;
}

void Particle::IncreaseScale(float scale)
{
    m_Scale += scale;
}