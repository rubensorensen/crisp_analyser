#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "glm/vec3.hpp"
#include "raw_model.hpp"

#include <memory>

class Particle
{
  public:

    Particle(const glm::vec3&, const glm::vec3&, float);
    ~Particle() = default;

    void IncreasePosition(const glm::vec3&);
    void IncreaseRotation(const glm::vec3&);
    void IncreaseScale(float);

    inline const RawModel& GetModel() const { return *m_Model; }
    inline const glm::vec3& GetPosition() const { return m_Position; }
    inline const glm::vec3& GetRotation() const { return m_Position; }
    inline const float GetScale() const { return m_Scale; }

  private:

    std::unique_ptr<RawModel> m_Model;
    glm::vec3 m_Position;
    glm::vec3 m_Rotation;
    float m_Scale;
};

#endif  // PARTICLE_HPP