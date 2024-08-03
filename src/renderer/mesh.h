#include "../core/defines.h"
#include "../core/logger.h"

#include "vertexArray.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"

#include "shader.h"
#include "texture.h"

class Mesh
{
    private:
    VertexArray va;
    VertexBuffer vb;
    IndexBuffer ib;

    VertexBufferLayout layout;

    std::vector<f32> vertices;
    std::vector<u32> indices;

    std::vector<Texture> textures;

    bool initialized;

    public:
    Mesh() : initialized{false} {}
    Mesh(std::vector<f32> vertices, std::vector<u32> indices, std::vector<Texture> textures);

    void Initialize(std::vector<f32> vertices, std::vector<u32> indices, std::vector<Texture> textures);

    ///______________ GETTERS ____________________
    inline VertexArray &GetVertexArray() { return va; }
    inline VertexBuffer &GetVertexBuffer() { return vb; }
    inline IndexBuffer &GetIndexBuffer() { return ib; }
    inline VertexBufferLayout &GetVertexBufferLayout() { return layout; }

    void Setup();

    void Render(Shader shader);

    ~Mesh() = default;
};