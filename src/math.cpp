#include "math.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

glm::mat4x4 Math::CreateTransformationMatrix(
    glm::vec3 translation, float rotX, float rotY, float rotZ, float scale)
{
    glm::mat4x4 matrix(1.0f);
    matrix = glm::translate(matrix, translation);
    matrix = glm::rotate(matrix, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
    matrix = glm::scale(matrix, glm::vec3(scale));
    return matrix;
}