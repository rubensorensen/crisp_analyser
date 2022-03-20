#ifndef MATH_HPP
#define MATH_HPP

#include "glm/mat4x4.hpp"

class Math
{
  public:

    static glm::mat4x4 CreateTransformationMatrix(glm::vec3, float, glm::vec3, float);

  private:

    Math()  = default;
    ~Math() = default;
};

#endif  // MATH_HPP