#ifndef RAW_MODEL_HPP
#define RAW_MODEL_HPP

#include <stdint.h>

class RawModel
{
  public:

    RawModel(uint32_t, uint32_t);

    inline uint32_t GetVertexArrayObject() const { return m_VertexArrayObjectID; }
    inline uint32_t GetVertexCount() const { return m_VertexCount; }

  private:

    uint32_t m_VertexArrayObjectID;
    uint32_t m_VertexCount;
};

#endif  // RAW_MODEL_HPP