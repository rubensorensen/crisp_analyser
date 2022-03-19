#ifndef LOADER_HPP
#define LOADER_HPP

#include "raw_model.hpp"

#include <list>
#include <stdio.h>

class Loader
{
  public:

    static RawModel LoadToVAO(float*, size_t);
    static void CleanUp();

  private:

    Loader() = default;

    static uint32_t CreateVAO();
    static void StoreDataInAttributeLists(uint32_t, float*, size_t);
    static void UnbindVAO();

  private:

    static std::list<uint32_t> m_VertexArrayObjects;
    static std::list<uint32_t> m_VertexBufferObjects;
};

#endif  // LOADER_HPP