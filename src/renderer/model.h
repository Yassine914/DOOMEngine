#include "../core/defines.h"
#include "../core/logger.h"

#include "mesh.h"

#include "../../thirdparty/include/glm/glm.hpp"
#include "../../thirdparty/include/glm/gtc/matrix_transform.hpp"

class Model
{
    public:
    std::vector<Mesh> meshes;
    Shader shader;

    public:
    Model() {}

    virtual void Initialize()
    {
        for(Mesh mesh : meshes)
            mesh.Setup(shader);
    }

    virtual void Render()
    {
        for(Mesh mesh : meshes)
            mesh.Render(shader);
    }

    virtual void Cleanup()
    {
        for(Mesh mesh : meshes)
            mesh.Cleanup();
    }
};