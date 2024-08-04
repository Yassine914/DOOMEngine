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
    Mesh::vertices = vertices;
    Mesh::indices = indices;
    Mesh::textures = textures;

    vb.Initialize(&vertices[0], sizeof(f32) * vertices.size());
    ib.Initialize(&indices[0], indices.size());

    initialized = true;
}

void Mesh::Setup(Shader &shader)
{
    LOGINIT_COUT();

    if(!initialized)
    {
        Log(LOG_ERROR, FILE_INFO) << "MESH: tried to initialize a mesh without data\n";
        return;
    }

    // TODO: fix binding and unbinding issues: rm va, vb classes
    va.Bind();
    vb.Bind();
    ib.Bind();
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib.GetID());

    // init vb layout
    layout.Push<f32>(3); // pos
    layout.Push<f32>(2); // tex

    // va.Bind();
    // va.AddBuffer(vb, layout);

    shader.Bind();
    for(u32 i = 0; i < textures.size(); i++)
    {
        shader.SetUniformInt(textures[i].name, i);
    }
}

void Mesh::Render(Shader &shader)
{
    shader.Bind();
    for(u32 i = 0; i < textures.size(); i++)
    {
        textures[i].Bind(i);
    }

    va.Bind();
    // ib.Bind();
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Mesh::Cleanup()
{
    va.Delete();
    vb.Delete();
    ib.Delete();
}