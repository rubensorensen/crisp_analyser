#ifndef MATH_HPP
#define MATH_HPP

#include "glm/glm.hpp"
#include "glm/mat4x4.hpp"

class Math
{
  public:

    static glm::mat4x4 CreateTransformationMatrix(glm::vec3, float, float, float, float);

  private:

    Math()  = default;
    ~Math() = default;
};

#endif  // MATH_HPP