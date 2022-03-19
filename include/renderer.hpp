#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "raw_model.hpp"

class Renderer
{
  public:

    Renderer()  = default;
    ~Renderer() = default;

    void Prepare();
    void RenderModel(const RawModel&);

  private:
};

#endif  // RENDERER_HPP