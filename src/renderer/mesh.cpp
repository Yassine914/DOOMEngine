#include "mesh.h"

// clang-format off
Mesh::Mesh(std::vector<f32> vertices, std::vector<u32> indices, std::vector<Texture> textures)
    : initialized{false}
{
    Initialize(vertices, indices, textures);
}

// clang-format on
void Mesh::Initialize(std::vector<f32> vertices, std::vector<u32> indices, std::vector<Texture> textures)
{
    vb.Initialize(&vertices[0], sizeof(vertices));
    ib.Initialize(&indices[0], indices.size());

    initialized = true;
    Setup();
}

void Mesh::Setup()
{
    LOGINIT_COUT();

    if(!initialized)
    {
        Log(LOG_ERROR, FILE_INFO) << "MESH: tried to initialize a mesh without data\n";
        return;
    }

    // init vb layout
    layout.Push<f32>(3); // pos
    layout.Push<f32>(2); // tex

    va.AddBuffer(vb, layout);

    va.Unbind();
}

void Mesh::Render(Shader shader)
{
    LOGINIT_COUT();
    if(!initialized)
    {
        Log(LOG_ERROR, FILE_INFO) << "MESH: tried to render a null mesh\n";
        return;
    }

    shader.Bind();
    for(u32 i = 0; i < textures.size(); i++)
    {
        shader.SetUniformInt(textures[i].name, textures[i].ID);
        textures[i].Bind(i);
    }

    va.Bind();
    ib.Bind();
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}
