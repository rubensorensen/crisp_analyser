#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "particle.hpp"
#include "raw_model.hpp"
#include "shader.hpp"

class Renderer
{
  public:

    static void NewFrame();
    static void RenderModel(const RawModel&);
    static void RenderParticle(const Particle&, Shader*);

  private:

    Renderer()  = default;
    ~Renderer() = default;
};

#endif  // RENDERER_HPP