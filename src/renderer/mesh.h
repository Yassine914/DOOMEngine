#pragma once

#include "../core/defines.h"

#include "../../thirdparty/include/glad/glad.h"

#include <vector>
#include "../../thirdparty/include/glm/glm.hpp"

#include "shader.h"
#include "texture.h"
#include "vertexBufferLayout.h"

struct Vertex
{
    glm::vec3 pos;
    glm::vec2 texCoord;

    static std::vector<Vertex> GenList(f32 *vertices, i32 numVertices);
};

class Mesh
{
    private:
    u32 VAO, VBO, EBO;
    VertexBufferLayout layout;

    public:
    std::vector<Vertex> vertices;
    std::vector<u32> indices;

    std::vector<Texture> textures;

    private:
    void Setup();

    public:
    Mesh();
    Mesh(std::vector<Vertex> &vertices, std::vector<u32> &indices, std::vector<Texture> &textures);

    void InitializeBufferLayout();
    void Render(Shader shader);

    void Cleanup();

    ~Mesh();
};