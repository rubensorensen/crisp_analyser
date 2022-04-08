#include "particle.hpp"

#include "loader.hpp"

#include <iostream>
#include <random>
#include <stdint.h>

static std::mt19937 rng(std::random_device{}());
static std::uniform_int_distribution<> dist(0, 100'000);

Particle::Particle(const glm::vec3& pos, const glm::vec3& rot, float scale)
    : m_Position(pos), m_Rotation(rot), m_Scale(scale), m_Offset(0)
{
    m_NoiseX         = siv::PerlinNoise(dist(rng));
    m_NoiseY         = siv::PerlinNoise(dist(rng));
    float vertices[] = {
        -0.5f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f
    };
    uint32_t indices[] = { 0, 1, 3, 3, 1, 2 };
    m_Model            = std::make_unique<RawModel>(
        Loader::LoadToVAO(vertices, sizeof(vertices), indices, sizeof(indices)));
}

void Particle::Update(double dt, float scale, float speed)
{
    m_Position.x = m_NoiseX.noise1D(m_Offset) * 3;
    m_Position.y = m_NoiseY.noise1D(m_Offset) * 3;
    m_Offset += speed * dt * 0.00001f;
    m_Scale = scale;
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