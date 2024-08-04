#include "mesh2.h"

// clang-format off

Mesh2::Mesh2(std::vector<f32> vertices, std::vector<u32> indices, std::vector<Texture> textures)
    :vertices{vertices}, indices{indices}, textures{textures}
{
    LOGINIT_COUT();

    glGenVertexArrays(1, &vertexArray);
    if(!glIsVertexArray(vertexArray))
    {
        Log(LOG_ERROR, FILE_INFO) << "the vertex array wasn't initialized...\n";
        exit(1);
    }

    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &indexBuffer);

    glBindVertexArray(vertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(f32), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u32), &indices[0], GL_STATIC_DRAW);

    AddVertexAttributes();
}

void Mesh2::AddVertexAttributes()
{
    // add layout elements
    layout.Push<f32>(3); // pos
    layout.Push<f32>(2); // tex

    const auto &elements = layout.GetElements();
    u32 offset = 0;
    for(u32 i = 0; i < elements.size(); i++)
    {
        const auto element = elements[i];
        glEnableVertexAttribArray(i);

        glVertexAttribPointer(i,
            element.count,
            element.type,
            element.normalized,
            layout.GetStride(),
            (const void *) (u64) offset
        );

        offset += element.count * LayoutElement::GetSizeOfType(element.type);
    }
}

// clang-format on

void Mesh2::Render(Shader &shader)
{
    for(u32 i = 0; i < textures.size(); i++)
    {
        shader.SetUniformInt(textures[i].name, i);
        textures[i].Bind(i);
    }

    LOGINIT_COUT();
    if(glIsVertexArray(vertexArray))
        LOG(LOG_DEBUG, "it is actually an array...\n");
    else
        LOG(LOG_DEBUG, "it is not an actuall VAO...\n");

    glBindVertexArray(vertexArray);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Mesh2::UnbindAll()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh2::Delete()
{
    glDeleteVertexArrays(1, &vertexArray);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &indexBuffer);
}

Mesh2::~Mesh2()
{
    Delete();
}