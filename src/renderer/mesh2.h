#include "../core/defines.h"
#include "../core/logger.h"

#include "vertexBufferLayout.h"

#include "shader.h"
#include "texture.h"

class Mesh2
{
    private:
    VertexBufferLayout layout;

    std::vector<f32> vertices;
    std::vector<u32> indices;

    std::vector<Texture> textures;

    public:
    u32 vertexArray, vertexBuffer, indexBuffer;

    private:
    void AddVertexAttributes();

    public:
    Mesh2(std::vector<f32> vertices, std::vector<u32> indices, std::vector<Texture> textures);

    ///______________ GETTERS ___________________
    inline VertexBufferLayout &GetVertexBufferLayout() { return layout; }

    void Render(Shader &shader);

    void UnbindAll();
    void Delete();

    ~Mesh2();
};