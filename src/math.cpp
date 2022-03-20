#include "math.hpp"

#include "glm/gtc/matrix_transform.hpp"

glm::mat4x4 Math::CreateTransformationMatrix(glm::vec3 translation,
                                             float angle,
                                             glm::vec3 rotation,
                                             float scale)
{
    glm::mat4x4 matrix(1.0f);
    matrix = glm::translate(matrix, translation);
    matrix = glm::rotate(matrix, glm::radians(angle), rotation);
    matrix = glm::scale(matrix, glm::vec3(scale));
    return matrix;
}