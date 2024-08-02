#include "../include/mats.h"

using namespace glm;

namespace mats {

// clang-format off
// returns a translation matrix
mat4 translateMat(float x, float y, float z)
{
    /*
    mat = 1, 0, 0, x
          0, 1, 0, y
          0, 0, 1, z
          0, 0, 0, 1
    */
    return mat4(1.0, 0.0, 0.0, 0.0, //first column(not first row)
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                x, y, z, 1);

}

// returns a matrix that performs a rotation on x axis
mat4 rotateXmat(float rad)
{
    /*
    mat = (1, 0, 0, 0
           0, cos, -sin, 0
           0, sin, cos, 0
           0, 0, 0, 1 )^Transposed
    */
    return mat4(1.0, 0.0, 0.0, 0.0,
                0.0, cos(rad), -sin(rad), 0.0,
                0.0, sin(rad), cos(rad), 0.0,
                0.0, 0.0, 0.0, 1);
}

// returns a matrix that performs a rotation on y axis
mat4 rotateYmat(float rad)
{
    return mat4(cos(rad), 0.0, sin(rad), 0.0,
                0.0, 1.0, 0.0, 0.0,
                -sin(rad), 0.0, cos(rad), 0.0,
                 0.0, 0.0, 0.0, 1.0);
}

// returns a matrix that performs a rotation on y axis
mat4 rotateZmat(float rad)
{
    return mat4(cos(rad), -sin(rad), 0.0, 0.0,
                sin(rad), cos(rad), 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0);
}

//returns a matrix that performs a scaling by x, y, and z
mat4 scaleMat(float x, float y, float z)
{
    return mat4(x, 0.0, 0.0, 0.0,
                0.0, y, 0.0, 0.0,
                0.0, 0.0, z, 0.0,
                0.0, 0.0, 0.0, 1.0);
}

// clang-format on
} // namespace mats