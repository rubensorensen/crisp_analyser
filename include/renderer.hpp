#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "raw_model.hpp"

class Renderer
{
  public:

    static void NewFrame();
    static void RenderModel(const RawModel&);

  private:

    Renderer()  = default;
    ~Renderer() = default;
};

#endif  // RENDERER_HPP