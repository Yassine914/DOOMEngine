#include "mesh.h"

// clang-format off

std::vector<Vertex> Vertex::GenList(f32 *vertices, i32 numVertices)
{
    std::vector<Vertex> ret(noVertices);
    i32 stride = sizeof(Vertex) / sizeof(f32);

    for(i32 i = 0; i < numVertices; i++)
    {
        ret[i].pos = glm::vec3(
            vertices[i * stride + 0],
            vertices[i * stride + 1],
            vertices[i * stride + 3]
        );

        ret[i].texCoord = glm::vec2(
            vertices[i * stride + 3],
            vertices[i * stride + 4]
        );
    }

    return ret;
}

// clang-format on