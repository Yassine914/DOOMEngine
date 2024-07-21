#include "glm/matrix.hpp"
#include "glm/trigonometric.hpp"

using namespace glm;

namespace mats {

mat4 translateMat(float x, float y, float z);
mat4 rotateXmat(float rad);
mat4 rotateYmat(float rad);
mat4 rotateZmat(float rad);
mat4 scaleMat(float x, float y, float z);

} // namespace mats