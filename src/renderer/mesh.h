#pragma once

#include "../core/defines.h"
#include "../core/logger.h"

#include "../../thirdparty/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <vector>
#include "../../thirdparty/include/glm/glm.hpp"

#include "shader.h"
#include "textserv.h"

struct Vertex
{
    glm::vec3 pos;
    glm::vec2 texCoord;

    static std::vector<Vertex> GenList(f32 *vertices, i32 numVertices);
};

class Mesh
{
};