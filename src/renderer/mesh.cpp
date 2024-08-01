#include "mesh.h"

#include <cstddef>

// clang-format off

// TODO: remove this useless function (if actually useless)
std::vector<Vertex> Vertex::GenList(f32 *vertices, i32 numVertices)
{
    std::vector<Vertex> ret(numVertices);
    i32 stride = sizeof(Vertex) / sizeof(f32);

    for(i32 i = 0; i < numVertices; i++)
    {
        ret[i].pos = glm::vec3(
            vertices[i * stride + 0], // x
            vertices[i * stride + 1], // y
            vertices[i * stride + 3]  // z
        );

        ret[i].texCoord = glm::vec2(
            vertices[i * stride + 3], // s
            vertices[i * stride + 4]  // t
        );
    }

    return ret;
}

// clang-format on

///____________________ MESH CLASS _____________________

Mesh::Mesh() {}

// clang-format off

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<u32> &indices, std::vector<Texture> &textures)
    :vertices{vertices}, indices{indices}, textures{textures}
{
    layout.Push<u32>(3);
    layout.Push<u32>(2);
}
// clang-format on

void Mesh::Setup()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u32), &indices[0], GL_STATIC_DRAW);

    layout.Push<u32>(3); // pos
    layout.Push<u32>(2); // texCoord

    InitializeBufferLayout();

    glBindVertexArray(0);
}

// clang-format off
void Mesh::InitializeBufferLayout()
{
    const auto &elements = layout.GetElements();
    u32 offset = 0;

    for(u32 i = 0; i < elements.size(); i++)
    {
        const auto &element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(
            i,
            element.count,
            element.type,
            element.normalized,
            layout.GetStride(),
            (void *) (u64) offset
        );

        offset += element.count * LayoutElement::GetSizeOfType(element.type);
    }
}
// clang-format on

void Mesh::Render(Shader shader)
{
    for(u32 i = 0; i < textures.size(); i++)
    {
        shader.SetUniformInt(textures[i].name, textures[i].ID);
        textures[i].MakeActive(i);
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

    // TODO: why clean every frame?
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::Cleanup()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}